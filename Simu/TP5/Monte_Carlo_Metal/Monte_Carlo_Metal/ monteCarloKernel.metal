//
//   monteCarloKernel.metal
//  Monte_Carlo_Metal
//
//  Created by Ao XIE on 29/12/2024.
//

#include <metal_stdlib>
using namespace metal;

kernel void monteCarloKernel(device float *results [[ buffer(0) ]],
                             uint id [[ thread_position_in_grid ]]) {
    float x = (float)(id % 1024) / 1024.0;
    float y = (float)((id / 1024) % 1024) / 1024.0;
    float z = (float)(id / (1024 * 1024)) / 1024.0;

    results[id] = (x * x + y * y + z * z <= 1.0) ? 1.0 : 0.0;
}
