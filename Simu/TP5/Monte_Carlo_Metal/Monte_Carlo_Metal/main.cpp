//
//  main.cpp
//  Monte_Carlo_Metal
//
//  Created by Ao XIE on 29/12/2024.
//

#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#include <iostream>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // 初始化 Metal 设备
        id<MTLDevice> device = MTLCreateSystemDefaultDevice();
        if (!device) {
            std::cerr << "当前设备不支持 Metal！" << std::endl;
            return -1;
        }
        std::cout << "Metal 设备已初始化: " << [[device name] UTF8String] << std::endl;

        // 加载 Metal Library
        NSError *error = nil;
        id<MTLLibrary> library = [device newDefaultLibrary];
        if (!library) {
            std::cerr << "无法加载 Metal Library: " << [[error localizedDescription] UTF8String] << std::endl;
            return -1;
        }

        // 创建 Pipeline
        id<MTLFunction> function = [library newFunctionWithName:@"monteCarloKernel"];
        if (!function) {
            std::cerr << "无法加载 Kernel 函数！" << std::endl;
            return -1;
        }
        id<MTLComputePipelineState> pipeline = [device newComputePipelineStateWithFunction:function error:&error];
        if (error) {
            std::cerr << "创建 Pipeline 失败: " << [[error localizedDescription] UTF8String] << std::endl;
            return -1;
        }

        // 准备计算任务（示例: 1024 个点）
        int numPoints = 1024;
        id<MTLBuffer> resultBuffer = [device newBufferWithLength:sizeof(float) * numPoints options:MTLResourceStorageModeShared];
        id<MTLCommandQueue> commandQueue = [device newCommandQueue];
        id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
        id<MTLComputeCommandEncoder> encoder = [commandBuffer computeCommandEncoder];
        [encoder setComputePipelineState:pipeline];
        [encoder setBuffer:resultBuffer offset:0 atIndex:0];

        MTLSize gridSize = MTLSizeMake(numPoints, 1, 1);
        MTLSize threadGroupSize = MTLSizeMake(256, 1, 1);
        [encoder dispatchThreads:gridSize threadsPerThreadgroup:threadGroupSize];
        [encoder endEncoding];
        [commandBuffer commit];
        [commandBuffer waitUntilCompleted];

        // 读取结果
        float *results = (float *)[resultBuffer contents];
        int insideSphere = 0;
        for (int i = 0; i < numPoints; ++i) {
            insideSphere += results[i];
        }

        float volume = (float)insideSphere / numPoints * 8.0;
        std::cout << "估算球体积为: " << volume << std::endl;
    }
    return 0;
}
