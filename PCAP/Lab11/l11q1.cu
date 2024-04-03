// write a program in CUDA to perform tiled matrix multiplication using 2D grid and 2D block

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define BLOCK_SIZE 16

// Kernel function for matrix multiplication
__global__ void matrixMul(float* A, float* B, float* C, int N) {
    __shared__ float tileA[BLOCK_SIZE][BLOCK_SIZE];
    __shared__ float tileB[BLOCK_SIZE][BLOCK_SIZE];

    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    float tmp = 0;
    for (int m = 0; m < (N / BLOCK_SIZE); ++m) {
        tileA[threadIdx.y][threadIdx.x] = A[row * N + m * BLOCK_SIZE + threadIdx.x];
        tileB[threadIdx.y][threadIdx.x] = B[(m * BLOCK_SIZE + threadIdx.y) * N + col];
        __syncthreads();

        for (int k = 0; k < BLOCK_SIZE; ++k) {
            tmp += tileA[threadIdx.y][k] * tileB[k][threadIdx.x];
        }
        __syncthreads();
    }
    C[row * N + col] = tmp;
}

int main() {
    int N = 1024; // Matrix size
    float *h_A, *h_B, *h_C;
    float *d_A, *d_B, *d_C;

    // Allocate memory on the host
    h_A = (float*)malloc(N * N * sizeof(float));
    h_B = (float*)malloc(N * N * sizeof(float));
    h_C = (float*)malloc(N * N * sizeof(float));

    // Initialize matrices
    for (int i = 0; i < N * N; i++) {
        h_A[i] = rand() / (float)RAND_MAX;
        h_B[i] = rand() / (float)RAND_MAX;
    }

    // Allocate memory on the device
    cudaMalloc((void**)&d_A, N * N * sizeof(float));
    cudaMalloc((void**)&d_B, N * N * sizeof(float));
    cudaMalloc((void**)&d_C, N * N * sizeof(float));

    // Copy matrices to the device
    cudaMemcpy(d_A, h_A, N * N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, N * N * sizeof(float), cudaMemcpyHostToDevice);

    // Perform matrix multiplication
    dim3 dimGrid(N / BLOCK_SIZE, N / BLOCK_SIZE);
    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
    matrixMul<<<dimGrid, dimBlock>>>(d_A, d_B, d_C, N);

    // Copy result back to the host
    cudaMemcpy(h_C, d_C, N * N * sizeof(float), cudaMemcpyDeviceToHost);

    // Free memory
    free(h_A);
    free(h_B);
    free(h_C);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
