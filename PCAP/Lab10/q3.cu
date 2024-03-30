/*
Write a CUDA program that reads a matrix A of size MXN and produce an output matrix B of same size such that
it replaces all the non-border elements(numbers in bold) of A with its equivalent 1's complement and remaining elements same as matrix A.
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void modifyMatrix(int *A, int *B, int M, int N) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    int col = blockIdx.y * blockDim.y + threadIdx.y;

    if (row < M && col < N) {
        int idx = row * N + col;
        if (row > 0 && row < M - 1 && col > 0 && col < N - 1) {
            B[idx] = ~A[idx]; // 1's complement for non-border elements
        } else {
            B[idx] = A[idx]; // Same as matrix A for border elements
        }
    }
}

int main() {
    int M, N;
    printf("Enter the number of rows (M): ");
    scanf("%d", &M);
    printf("Enter the number of columns (N): ");
    scanf("%d", &N);
    int *A = (int *)malloc(M * N * sizeof(int));
    int *B = (int *)malloc(M * N * sizeof(int));

    // Input the matrix
    printf("Enter the matrix elements:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i * N + j]);
        }
    }

    // Allocate device memory
    int *d_A, *d_B;
    cudaMalloc((void **)&d_A, M * N * sizeof(int));
    cudaMalloc((void **)&d_B, M * N * sizeof(int));

    // Copy data to device
    cudaMemcpy(d_A, A, M * N * sizeof(int), cudaMemcpyHostToDevice);

    // Perform the operation
    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((N + threadsPerBlock.x - 1) / threadsPerBlock.x, (M + threadsPerBlock.y - 1) / threadsPerBlock.y);
    modifyMatrix<<<numBlocks, threadsPerBlock>>>(d_A, d_B, M, N);

    // Copy the result back to the host
    cudaMemcpy(B, d_B, M * N * sizeof(int), cudaMemcpyDeviceToHost);

    // Print the result
    printf("Modified matrix B:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", B[i * N + j]);
        }
        printf("\n");
    }

    // Free device memory
    cudaFree(d_A);
    cudaFree(d_B);
    free(A);
    free(B);

    return 0;
}
