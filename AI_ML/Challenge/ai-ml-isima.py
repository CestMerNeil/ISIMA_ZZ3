#!/usr/bin/env python
# coding: utf-8

# # Challenge Deep Learning
# 
# L'objectif de ce challenge est de proposer une méthode de classification, basée sur des réseaux de neurones, permettant de classer des images de champignons.
# Le jeu de données proposé comprend 3 classes balancées
# 
# Vous pouvez utiliser tout algorithme qui vous semble pertinent (PMC, CNN,), en faisant varier les données d'entrée (normalisation, augmentation de données,...), les paramètres des réseaux considérés (fonction objectif, optimiseur, dropout, learning rate, taille des batchs...)
# 
# Vous devez prendre en compte la spécificité des données (peu d'exemples, images de tailles différentes,...) pour construire vos jeux d'apprentissage et de test.
# 
# Bien sûr, pour valider votre travail, nous ferons tourner le code en local, sur une base que nous conservons, pour voir si les résultats que vous proposez sont reproductibles.
# 
# Le compte-rendu sera effectué sur un notebook jupyter, dans lequel vous reporterez votre méthodologie en markdown, et vos codes en Python. Vous **expliquerez votre démarche**, **justifierez vos choix**, **commenterez vos expérimentations et vos résultats**.
# 
# La notation sera construite de la manière suivante :
# - 12 points sur le compte-rendu
# - 8 points seront accordés sur un classement par le taux de reconnsaissance des objets de la base de test.
# 
# Le notebook sera déposé sur la plateforme moodle du cours.

# In[2]:


import os
import zipfile
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image


# In[3]:


dataset_path = 'mushrooms' # A modifier


# In[4]:


def Data():
    data_dir = dataset_path
    classes = [cls for cls in os.listdir(data_dir) if os.path.isdir(os.path.join(data_dir, cls)) and not cls.startswith('.')]
    
    print("Classes:", classes)

    data_list = []
    for label in classes:
        image_files = os.listdir(os.path.join(data_dir,label))
        data_list.extend([(label,os.path.join(data_dir,label,f)) for f in image_files])

    print("Nombre d'images total:",len(data_list))
    print("Nombre d'images par classes:",[len(os.listdir(os.path.join(data_dir,label))) for label in classes])

    return data_list


# In[5]:


data_list = Data()


# In[6]:


image_samples = np.random.randint(0,high=len(data_list)-1, size=8)

fig = plt.figure(figsize=(16,6))
for i,img_idx in enumerate(image_samples):
    axs = fig.add_subplot(2,4,i+1)
    axs.set_title(data_list[img_idx][0])
    image = Image.open(data_list[img_idx][1])
    plt.imshow(image)
    plt.axis('off')

plt.suptitle("Exemples de données")
plt.tight_layout()


# # Solution

# In[9]:


import torch
import torch.nn as nn
import torch.nn.functional as F
from tqdm import tqdm
from torchvision import datasets, transforms
from torch.utils.data import DataLoader, random_split, Subset
from sklearn.model_selection import KFold
from torch.optim.lr_scheduler import StepLR


# ## ResNet-9
# For the ResNet family, ResNet-18, ResNet-50 are too large for a classification task like this, which contains 1640 imgs in 3 classes.
# So we chose a simplified model with a ResNet architecture, ResNet-9.
# 
# I tried a 3-layer CNN network, which may not be able to learn sufficient features because the model is too shallow. I also tried the smaller Transformer network with similarly unsatisfactory results.

# In[10]:


class ResidualBlock(nn.Module):
    def __init__(self, in_channels, out_channels, stride=1):
        super(ResidualBlock, self).__init__()

        self.conv1 = nn.Conv2d(in_channels, out_channels, kernel_size=3, stride=stride, padding=1, bias=False)
        self.bn1 = nn.BatchNorm2d(out_channels)
        self.relu = nn.ReLU(inplace=True)

        self.conv2 = nn.Conv2d(out_channels, out_channels, kernel_size=3, stride=1, padding=1, bias=False)
        self.bn2 = nn.BatchNorm2d(out_channels)

        self.shortcut = nn.Sequential()
        if stride != 1 or in_channels != out_channels:
            self.shortcut = nn.Sequential(
                nn.Conv2d(in_channels, out_channels, kernel_size=1, stride=stride, bias=False),
                nn.BatchNorm2d(out_channels)
            )

    def forward(self, x):
        out = self.relu(self.bn1(self.conv1(x)))
        out = self.bn2(self.conv2(out))
        out += self.shortcut(x)
        out = self.relu(out)
        return out


class ResNet(nn.Module):
    def __init__(self, block, num_classes=10):
        super(ResNet, self).__init__()
        self.in_channels = 64

        self.conv1 = nn.Conv2d(3, 64, kernel_size=3, stride=1, padding=1, bias=False)
        self.bn1 = nn.BatchNorm2d(64)
        self.relu = nn.ReLU(inplace=True)

        self.layer1 = self._make_layer(block, 64, stride=1)
        self.layer2 = self._make_layer(block, 128, stride=2)

        self.avg_pool = nn.AdaptiveAvgPool2d((1, 1))
        self.fc = nn.Linear(128, num_classes)

    def _make_layer(self, block, out_channels, stride):
        layer = block(self.in_channels, out_channels, stride)
        self.in_channels = out_channels
        return layer

    def forward(self, x):
        out = self.relu(self.bn1(self.conv1(x)))
        out = self.layer1(out)
        out = self.layer2(out)
        out = self.avg_pool(out)
        out = out.view(out.size(0), -1)
        out = self.fc(out)
        return out


# In[11]:


def train_epoch(model, train_loader, criterion, optimizer, device, class_name=None):
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


# ## Load Data
# 
# 
# In the beginning we were going to randomly classify the images according to 8 to 1 to 1 to get the training set, validation set and test set, but the amount of data was just too small. Therefore, ten per cent of the data is extracted as the test set, i.e., the model will not see this part of the images during the training process to verify the robustness of the model. For the remaining data, K-fold cross validation is used to improve the data utilisation.

# In[12]:


torch.manual_seed(42)
if torch.cuda.is_available():
    torch.cuda.manual_seed(42)

batch_size = 64
num_epochs = 200
num_workers = 4
learning_rate = 1e-3

train_transform = transforms.Compose([
    transforms.Resize(224),
    transforms.RandomResizedCrop(224, scale=(0.8, 1.0)),
    transforms.RandomHorizontalFlip(),
    transforms.RandomRotation(30),
    transforms.ColorJitter(brightness=0.2, contrast=0.2, saturation=0.2, hue=0.1),
    transforms.RandomAffine(degrees=0, translate=(0.1, 0.1)),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
])

val_transform = transforms.Compose([
    transforms.Resize(224),
    transforms.CenterCrop(224),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
])


# In[13]:


print("Telechargement datasets...")
dataset = datasets.ImageFolder(root=dataset_path, transform=train_transform)
print(f"Taille total de dataset : {len(dataset)}")
print(f"Classes: {dataset.classes}")

test_ratio = 0.1
total_size = len(dataset)
test_size = int(total_size * test_ratio)
train_val_size = int(total_size - test_size)

generator = torch.Generator().manual_seed(42)
train_val_dataset, test_dataset = random_split(dataset, [train_val_size, test_size], generator=generator)

test_dataset.dataset.transform = val_transform

k_folds = 5
kf = KFold(n_splits=k_folds, shuffle=True, random_state=42)


# ## Training

# In[ ]:


import warnings
warnings.filterwarnings(
    "ignorer", 
    message="Les images de palette avec une transparence exprimée en octets doivent être converties en images RGBA"
)

device = torch.device('cuda' if torch.cuda.is_available() else 
                     'mps' if torch.backends.mps.is_available() else 'cpu')
print(f"\nUtilisation de l'appareil: {device}")

os.makedirs('outputs', exist_ok=True)
fold_results = []
print("\nDebut entrainment de model...")

for fold, (train_idx, val_idx) in enumerate(kf.split(range(len(train_val_dataset)))):
    print(f"\nFold {fold + 1}/{k_folds}")
    
    train_subset = Subset(train_val_dataset, train_idx)
    val_subset = Subset(train_val_dataset, val_idx)
    
    train_loader = DataLoader(train_subset, batch_size=batch_size, 
                              shuffle=True, num_workers=num_workers)
    val_loader = DataLoader(val_subset, batch_size=batch_size, 
                            shuffle=False, num_workers=num_workers)
    
    print(f"entrainement taille: {len(train_subset)}")
    print(f"validation taille: {len(val_subset)}")
    
    model = ResNet(ResidualBlock, num_classes=len(dataset.classes)).to(device)
    optimizer = torch.optim.AdamW(model.parameters(), lr=learning_rate, weight_decay=1e-4)
    scheduler = StepLR(optimizer, step_size=180, gamma=0.1)
    criterion = torch.nn.CrossEntropyLoss()
    
    best_val_acc = 0
    for epoch in range(num_epochs):
        train_loss, train_acc = train_epoch(model, train_loader, criterion, optimizer, device)
        val_loss, val_acc = evaluate(model, val_loader, criterion, device)
        print(f"Epoch {epoch + 1}/{num_epochs} - "
              f"entrainement pertes: {train_loss:.4f}, entrainement precision: {train_acc:.2f}% - "
              f"perte validation: {val_loss:.4f}, precision validation: {val_acc:.2f}% - "
              f"Taux apprentissage: {scheduler.get_last_lr()[0]:.6f}")
        
        scheduler.step()
        
        if val_acc > best_val_acc:
            best_val_acc = val_acc
            best_model_path = f'outputs/best_model_fold{fold+1}.pth'
            torch.save(model.state_dict(), best_model_path)
            print(f"Meilleur modele enregistre pour Fold {fold + 1} a l'Epoch {epoch + 1} avec precision validation: {best_val_acc:.2f}%")
    
    fold_results.append(best_val_acc)

print("\n Resultats Cross Validation K-Fold:")
print(f"Fold Precision: {fold_results}")
print(f"Precision Moyenne: {sum(fold_results) / len(fold_results):.2f}%")


# ## Test

# In[12]:


def test_model(model, test_loader, criterion, device, model_path):
    print(f"\n Telechargement du model: {model_path}")
    model.load_state_dict(torch.load(model_path))
    model.to(device)
    test_loss, test_acc = evaluate(model, test_loader, criterion, device)
    
    print("\nTest Set Evaluation:")
    print(f"Test pertes: {test_loss:.4f}")
    print(f"Test precision: {test_acc:.2f}%")
    return test_loss, test_acc

test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False, num_workers=num_workers)

best_model_paths = [
    "/kaggle/working/outputs/best_model_fold1.pth",
    "/kaggle/working/outputs/best_model_fold2.pth",
    "/kaggle/working/outputs/best_model_fold3.pth",
    "/kaggle/working/outputs/best_model_fold4.pth",
    "/kaggle/working/outputs/best_model_fold5.pth"
]

for i, model_path in enumerate(best_model_paths):
    print(f"\nTeste du model pour Fold {i + 1}:")
    model_instance = ResNet(ResidualBlock, num_classes=len(dataset.classes))  # Create a new model instance
    test_loss, test_acc = test_model(
        model=model_instance,
        test_loader=test_loader,
        criterion=torch.nn.CrossEntropyLoss(),
        device=device,
        model_path=model_path
    )
    print(f"Fold {i + 1} - Test pertes: {test_loss:.4f}, Test precision: {test_acc:.2f}%")


# # ResNet-19 with pretrained model
# 

# In[ ]:


import torch
import torch.nn as nn
import torch.nn.functional as F
from tqdm import tqdm
from torchvision import datasets, transforms
from torch.utils.data import DataLoader, random_split
from torch.optim.lr_scheduler import StepLR

"""
import warnings
warnings.filterwarnings(
    "ignorer", 
    message="Les images de palette avec une transparence exprimée en octets doivent être converties en images RGBA"
)
"""
dataset_path = "mushrooms"  # A modifier
batch_size = 64
num_workers = 4
num_epochs = 10
learning_rate = 1e-3

device = torch.device('cuda' if torch.cuda.is_available() else 
                     'mps' if torch.backends.mps.is_available() else 'cpu')
print("Utilisation de l'appareil :", device)

train_transform = transforms.Compose([
    transforms.Resize(256),
    transforms.RandomResizedCrop(224, scale=(0.8, 1.0)),
    transforms.RandomHorizontalFlip(),
    transforms.RandomRotation(30),
    transforms.ColorJitter(brightness=0.2, contrast=0.2, saturation=0.2, hue=0.1),
    transforms.RandomAffine(degrees=0, translate=(0.1, 0.1)),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
])

val_transform = transforms.Compose([
    transforms.Resize(256),
    transforms.CenterCrop(224),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
])

full_dataset = datasets.ImageFolder(root=dataset_path, transform=train_transform)

test_ratio = 0.1
val_ratio = 0.1
total_size = len(full_dataset)
test_size = int(total_size * test_ratio)
val_size = int(total_size * val_ratio)
train_val_size = total_size - test_size

generator = torch.Generator().manual_seed(42)
train_val_dataset, test_dataset = random_split(
    full_dataset, [train_val_size, test_size], generator=generator
)
train_dataset, val_dataset = random_split(
    train_val_dataset, [train_val_size - val_size, val_size], generator=generator
)

test_dataset.dataset.transform = val_transform
val_dataset.dataset.transform = val_transform

train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True, num_workers=num_workers)
val_loader   = DataLoader(val_dataset,   batch_size=batch_size, shuffle=False, num_workers=num_workers)
test_loader  = DataLoader(test_dataset,  batch_size=batch_size, shuffle=False, num_workers=num_workers)

ResNet18 = torch.hub.load('pytorch/vision:v0.9.0', 'resnet18', pretrained=True)
ResNet18.fc = nn.Linear(512, 3)
ResNet18.to(device)

criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.AdamW(ResNet18.parameters(), lr=learning_rate, weight_decay=1e-4)
scheduler = StepLR(optimizer, step_size=80, gamma=0.1)

best_val_acc = 0.0  

for epoch in range(num_epochs):
    ResNet18.train()
    running_train_loss = 0.0
    correct_train = 0
    total_train = 0

    pbar = tqdm(train_loader, desc=f"Epoch [{epoch+1}/{num_epochs}] - Training")
    for inputs, targets in pbar:
        inputs, targets = inputs.to(device), targets.to(device)

        optimizer.zero_grad()
        outputs = ResNet18(inputs)
        loss = criterion(outputs, targets)
        loss.backward()
        optimizer.step()

        running_train_loss += loss.item()
        _, predicted = outputs.max(1)
        total_train += targets.size(0)
        correct_train += predicted.eq(targets).sum().item()
    
    train_loss = running_train_loss / len(train_loader)
    train_acc = 100.0 * correct_train / total_train

    ResNet18.eval()
    running_val_loss = 0.0
    correct_val = 0
    total_val = 0

    with torch.no_grad():
        for inputs, targets in val_loader:
            inputs, targets = inputs.to(device), targets.to(device)
            outputs = ResNet18(inputs)
            loss = criterion(outputs, targets)

            running_val_loss += loss.item()
            _, predicted = outputs.max(1)
            total_val += targets.size(0)
            correct_val += predicted.eq(targets).sum().item()

    val_loss = running_val_loss / len(val_loader)
    val_acc = 100.0 * correct_val / total_val

    scheduler.step()

    print(f"Epoch [{epoch+1}/{num_epochs}] "
          f"entrainment pertes: {train_loss:.4f} | entrainment precision: {train_acc:.2f}% "
          f"Validation pertes: {val_loss:.4f} | Validation precision: {val_acc:.2f}%")

    if val_acc > best_val_acc:
        best_val_acc = val_acc
        torch.save(ResNet18.state_dict(), "best_resnet18.pth")


ResNet18.eval()
test_loss = 0.0
correct_test = 0
total_test = 0

with torch.no_grad():
    for inputs, targets in test_loader:
        inputs, targets = inputs.to(device), targets.to(device)
        outputs = ResNet18(inputs)
        loss = criterion(outputs, targets)
        
        test_loss += loss.item()
        _, predicted = outputs.max(1)
        total_test += targets.size(0)
        correct_test += predicted.eq(targets).sum().item()

test_loss = test_loss / len(test_loader)
test_acc = 100.0 * correct_test / total_test
print(f"Test pertes: {test_loss:.4f} | Test precision: {test_acc:.2f}%")


# ## Pour installer conda et env
# ```
# conda create -n AI_ML python=3.12
# conda activate AI_ML
# pip install --upgrade pip
# pip install -r requirements.txt
# ```

# 
