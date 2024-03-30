/* Write a program in CUDA to read MXN matrix A and replace 1st row of this matrix by same elements,
 2nd row elements by square of each element and 3rd row elements by cube of each element and so on. */

 #include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void modifyMatrix(float *A, int M, int N) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    int col = blockIdx.y * blockDim.y + threadIdx.y;

    if (row < M && col < N) {
        int idx = row * N + col;
        float power = row + 1;
        A[idx] = pow(A[idx], power);
    }
}

int main() {
    int M, N;
    printf("Enter the number of rows (M): ");
    scanf("%d", &M);
    printf("Enter the number of columns (N): ");
    scanf("%d", &N);

    // Allocate memory for the matrix
    float *A = (float *)malloc(M * N * sizeof(float));

    // Input the matrix
    printf("Enter the matrix elements:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%f", &A[i * N + j]);
        }
    }

    // Allocate device memory
    float *d_A;
    cudaMalloc((void **)&d_A, M * N * sizeof(float));

    // Copy data to device
    cudaMemcpy(d_A, A, M * N * sizeof(float), cudaMemcpyHostToDevice);

    // Perform the operation
    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((N + threadsPerBlock.x - 1) / threadsPerBlock.x, (M + threadsPerBlock.y - 1) / threadsPerBlock.y);
    modifyMatrix<<<numBlocks, threadsPerBlock>>>(d_A, M, N);

    // Copy the result back to the host
    cudaMemcpy(A, d_A, M * N * sizeof(float), cudaMemcpyDeviceToHost);

    // Print the result
    printf("Modified matrix:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%f ", A[i * N + j]);
        }
        printf("\n");
    }

    // Free device memory
    cudaFree(d_A);
    free(A);

    return 0;
}
