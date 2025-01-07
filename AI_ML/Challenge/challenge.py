# challenge.py
import os
import torch
import torch.nn as nn
import torch.nn.functional as F
import numpy as np
from PIL import Image
from tqdm import tqdm
from torchvision import datasets, transforms
from torch.utils.data import DataLoader, random_split

class MushroomNet(nn.Module):
    def __init__(self):
        super(MushroomNet, self).__init__()
        # 第一个卷积块
        self.conv1 = nn.Conv2d(3, 32, kernel_size=3, padding=1)  # 添加padding保持尺寸
        self.bn1 = nn.BatchNorm2d(32)
        
        # 第二个卷积块
        self.conv2 = nn.Conv2d(32, 64, kernel_size=3, padding=1)
        self.bn2 = nn.BatchNorm2d(64)
        
        # 第三个卷积块
        self.conv3 = nn.Conv2d(64, 128, kernel_size=3, padding=1)
        self.bn3 = nn.BatchNorm2d(128)
        
        # 计算全连接层的输入维度
        # 输入图像224x224
        # 经过三次maxpool(2,2)后，特征图大小变为28x28
        # 因此特征维度为128*28*28
        self.dropout = nn.Dropout(0.5)
        self.fc1 = nn.Linear(128 * 28 * 28, 256)
        self.fc2 = nn.Linear(256, 3)

    def forward(self, x):
        # 第一个卷积块
        x = self.conv1(x)
        x = self.bn1(x)
        x = F.relu(x)
        x = F.max_pool2d(x, 2)  # 112x112

        # 第二个卷积块
        x = self.conv2(x)
        x = self.bn2(x)
        x = F.relu(x)
        x = F.max_pool2d(x, 2)  # 56x56

        # 第三个卷积块
        x = self.conv3(x)
        x = self.bn3(x)
        x = F.relu(x)
        x = F.max_pool2d(x, 2)  # 28x28

        # 展平
        x = x.view(x.size(0), -1)  # batch_size x (128*28*28)

        # 全连接层
        x = self.dropout(x)
        x = F.relu(self.fc1(x))
        x = self.dropout(x)
        x = self.fc2(x)

        return x

def train_epoch(model, train_loader, criterion, optimizer, device):
    model.train()
    running_loss = 0.0
    correct = 0
    total = 0
    
    pbar = tqdm(train_loader, desc='Training')
    for inputs, targets in pbar:
        inputs, targets = inputs.to(device), targets.to(device)
        
        optimizer.zero_grad()
        outputs = model(inputs)
        loss = criterion(outputs, targets)
        loss.backward()
        optimizer.step()
        
        running_loss += loss.item()
        _, predicted = outputs.max(1)
        total += targets.size(0)
        correct += predicted.eq(targets).sum().item()
        
        pbar.set_postfix({'loss': running_loss/total, 'acc': 100.*correct/total})
    
    return running_loss/len(train_loader), 100.*correct/total

def evaluate(model, data_loader, criterion, device):
    model.eval()
    running_loss = 0.0
    correct = 0
    total = 0
    
    with torch.no_grad():
        for inputs, targets in data_loader:
            inputs, targets = inputs.to(device), targets.to(device)
            outputs = model(inputs)
            loss = criterion(outputs, targets)
            
            running_loss += loss.item()
            _, predicted = outputs.max(1)
            total += targets.size(0)
            correct += predicted.eq(targets).sum().item()
    
    return running_loss/len(data_loader), 100.*correct/total

def predict_image(model, image_path, device, transform):
    model.eval()
    # Load and preprocess the image
    image = Image.open(image_path).convert('RGB')
    input_tensor = transform(image).unsqueeze(0).to(device)
    
    with torch.no_grad():
        output = model(input_tensor)
        probabilities = F.softmax(output, dim=1)
        prediction = output.argmax(dim=1).item()
        confidence = probabilities[0][prediction].item()
    
    return prediction, confidence

def main():
    # 设置随机种子以保证可重复性
    torch.manual_seed(42)
    if torch.cuda.is_available():
        torch.cuda.manual_seed(42)
    
    # Hyperparameters
    dataset_path = 'mushrooms'
    train_ratio = 0.8
    val_ratio = 0.1
    test_ratio = 0.1
    batch_size = 32
    num_epochs = 30
    num_workers = 0  # 在MacOS上设为0以避免多进程问题
    learning_rate = 0.001
    scheduler_factor = 0.1
    scheduler_patience = 2
    
    # Data transforms
    train_transform = transforms.Compose([
        transforms.Resize(224),
        transforms.CenterCrop(224),
        transforms.RandomHorizontalFlip(),
        transforms.RandomRotation(15),
        transforms.ColorJitter(brightness=0.2, contrast=0.2, saturation=0.2, hue=0.1),
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
    ])

    val_transform = transforms.Compose([
        transforms.Resize(224),
        transforms.CenterCrop(224),
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
    ])

    # Dataset setup
    print("Loading dataset...")
    dataset = datasets.ImageFolder(root=dataset_path, transform=train_transform)
    print(f"Total dataset size: {len(dataset)}")
    print(f"Classes: {dataset.classes}")
    
    total_size = len(dataset)
    train_size = int(train_ratio * total_size)
    val_size = int(val_ratio * total_size)
    test_size = total_size - train_size - val_size

    # 使用固定的随机种子进行数据集划分
    generator = torch.Generator().manual_seed(42)
    train_dataset, val_dataset, test_dataset = random_split(
        dataset, 
        [train_size, val_size, test_size],
        generator=generator
    )
    
    val_dataset.dataset.transform = val_transform
    test_dataset.dataset.transform = val_transform

    print(f"\nDataset splits:")
    print(f"Training: {len(train_dataset)}")
    print(f"Validation: {len(val_dataset)}")
    print(f"Test: {len(test_dataset)}")

    train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True, num_workers=num_workers)
    val_loader = DataLoader(val_dataset, batch_size=batch_size, shuffle=False, num_workers=num_workers)
    test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False, num_workers=num_workers)

    # Device setup
    device = torch.device('cuda' if torch.cuda.is_available() else 'mps' if torch.backends.mps.is_available() else 'cpu')
    print(f"\nUsing device: {device}")

    # Model setup
    model = MushroomNet().to(device)
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
    scheduler = torch.optim.lr_scheduler.ReduceLROnPlateau(
        optimizer, 
        mode='min',
        factor=scheduler_factor, 
        patience=scheduler_patience, 
        verbose=True
    )

    # 创建输出目录
    os.makedirs('outputs', exist_ok=True)
    best_model_path = 'outputs/best_model.pth'
    
    # Training
    best_val_acc = 0
    best_epoch = 0
    print("\nStarting training...")
    
    for epoch in range(num_epochs):
        print(f"\nEpoch {epoch+1}/{num_epochs}")
        
        # Train phase
        train_loss, train_acc = train_epoch(model, train_loader, criterion, optimizer, device)
        print(f"Training Loss: {train_loss:.4f}, Training Accuracy: {train_acc:.2f}%")
        
        # Validation phase
        val_loss, val_acc = evaluate(model, val_loader, criterion, device)
        print(f"Validation Loss: {val_loss:.4f}, Validation Accuracy: {val_acc:.2f}%")
        
        # Learning rate scheduling
        scheduler.step(val_loss)
        
        # Save best model
        if val_acc > best_val_acc:
            best_val_acc = val_acc
            best_epoch = epoch
            torch.save({
                'epoch': epoch,
                'model_state_dict': model.state_dict(),
                'optimizer_state_dict': optimizer.state_dict(),
                'val_acc': val_acc,
            }, best_model_path)
            print(f"Saved new best model with validation accuracy: {val_acc:.2f}%")

    print(f"\nTraining completed. Best validation accuracy: {best_val_acc:.2f}% at epoch {best_epoch+1}")
    
    # Final evaluation
    print("\nLoading best model for final evaluation...")
    checkpoint = torch.load(best_model_path)
    model.load_state_dict(checkpoint['model_state_dict'])
    test_loss, test_acc = evaluate(model, test_loader, criterion, device)
    print(f"Final Test Loss: {test_loss:.4f}, Test Accuracy: {test_acc:.2f}%")

    # Save final results
    results = {
        'best_validation_accuracy': float(best_val_acc),
        'best_epoch': best_epoch + 1,
        'final_test_accuracy': float(test_acc),
        'final_test_loss': float(test_loss),
    }
    
    import json
    with open('outputs/results.json', 'w') as f:
        json.dump(results, f, indent=4)
    print("\nResults saved to outputs/results.json")

if __name__ == '__main__':
    main()