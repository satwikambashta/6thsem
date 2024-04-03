// write a program in cuda to perform tiled 1d convolution 
// operation on the input array N of size width using the mask array ,  M of size mask_width, to produce the resultant array P of size width. 

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define BLOCK_SIZE 256

// Kernel function for tiled 1D convolution
__global__ void tiledConvolution1D(float *N, float *M, float *P, int width, int mask_width) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    if (idx < width) {
        float sum = 0;
        for (int i = 0; i < mask_width; i++) {
            int inputIndex = idx + i - mask_width / 2;
            if (inputIndex >= 0 && inputIndex < width) {
                sum += N[inputIndex] * M[i];
            }
        }
        P[idx] = sum;
    }
}

int main() {
    int width = 1024; // Size of the input array
    int mask_width = 5; // Size of the mask array

    float *h_N = (float*)malloc(width * sizeof(float));
    float *h_M = (float*)malloc(mask_width * sizeof(float));
    float *h_P = (float*)malloc(width * sizeof(float));

    // Initialize input and mask arrays
    for (int i = 0; i < width; i++) {
        h_N[i] = rand() / (float)RAND_MAX;
    }
    for (int i = 0; i < mask_width; i++) {
        h_M[i] = rand() / (float)RAND_MAX;
    }

    // Allocate device memory
    float *d_N, *d_M, *d_P;
    cudaMalloc((void**)&d_N, width * sizeof(float));
    cudaMalloc((void**)&d_M, mask_width * sizeof(float));
    cudaMalloc((void**)&d_P, width * sizeof(float));

    // Copy input and mask arrays to device
    cudaMemcpy(d_N, h_N, width * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, h_M, mask_width * sizeof(float), cudaMemcpyHostToDevice);

    // Define block and grid sizes
    int blockSize = BLOCK_SIZE;
    int gridSize = (width + blockSize - 1) / blockSize;

    // Perform tiled 1D convolution
    tiledConvolution1D<<<gridSize, blockSize>>>(d_N, d_M, d_P, width, mask_width);

    // Copy resultant array back to host
    cudaMemcpy(h_P, d_P, width * sizeof(float), cudaMemcpyDeviceToHost);

    // Free memory
    free(h_N);
    free(h_M);
    free(h_P);
    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);

    return 0;
}
