/*Write a program in CUDA to perform parallel Sparse Matrix Vector multiplication using 
compressed sparse row (CSR) storage format.
Represent the input sparse matrix in CSR format in the host code.*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void spmv_csr(const int *csrRowPtrA, const int *csrColIndA, const float *csrValA, const float *x, float *y, int m) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < m) {
        
        float sum = 0.0f;
        for (int i = csrRowPtrA[row]; i < csrRowPtrA[row + 1]; i++) {
            sum += csrValA[i] * x[csrColIndA[i]];
        }
        y[row] = sum;
    }
}

int main() {
    int m, n, nnz;
    printf("Enter the number of rows (m): ");
    scanf("%d", &m);
    printf("Enter the number of columns (n): ");
    scanf("%d", &n);
    printf("Enter the number of non-zero elements (nnz): ");
    scanf("%d", &nnz);

    // Allocate memory for the original matrix and the CSR format
    float *A = (float *)malloc(m * n * sizeof(float));
    int *csrRowPtrA = (int *)malloc((m + 1) * sizeof(int));
    int *csrColIndA = (int *)malloc(nnz * sizeof(int));
    float *csrValA = (float *)malloc(nnz * sizeof(float));

    // Input the original matrix
    printf("Enter the matrix elements:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%f", &A[i * n + j]);
            if (A[i * n + j] != 0.0f) {
                csrValA[csrRowPtrA[i]] = A[i * n + j];
                csrColIndA[csrRowPtrA[i]] = j;
                csrRowPtrA[i + 1] = csrRowPtrA[i] + 1;
            }
        }
    }

    // Allocate device memory
    int *d_csrRowPtrA, *d_csrColIndA;
    float *d_csrValA, *d_x, *d_y;
    cudaMalloc((void **)&d_csrRowPtrA, (m + 1) * sizeof(int));
    cudaMalloc((void **)&d_csrColIndA, nnz * sizeof(int));
    cudaMalloc((void **)&d_csrValA, nnz * sizeof(float));
    cudaMalloc((void **)&d_x, n * sizeof(float));
    cudaMalloc((void **)&d_y, m * sizeof(float));

    // Copy data to device
    cudaMemcpy(d_csrRowPtrA, csrRowPtrA, (m + 1) * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_csrColIndA, csrColIndA, nnz * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_csrValA, csrValA, nnz * sizeof(float), cudaMemcpyHostToDevice);

    // Input the vector
    printf("Enter the vector elements:\n");
    float *x = (float *)malloc(n * sizeof(float));
    for (int i = 0; i < n; i++) {
        scanf("%f", &x[i]);
    }
    cudaMemcpy(d_x, x, n * sizeof(float), cudaMemcpyHostToDevice);

    // Perform the multiplication
    spmv_csr<<<(m + 255) / 256, 256>>>(d_csrRowPtrA, d_csrColIndA, d_csrValA, d_x, d_y, m);

    // Copy the result back to the host
    float *y = (float *)malloc(m * sizeof(float));
    cudaMemcpy(y, d_y, m * sizeof(float), cudaMemcpyDeviceToHost);

    // Print the result
    printf("Result: ");
    for (int i = 0; i < m; i++) {
        printf("%f ", y[i]);
    }
    printf("\n");

    // Free device memory
    cudaFree(d_csrRowPtrA);
    cudaFree(d_csrColIndA);
    cudaFree(d_csrValA);
    cudaFree(d_x);
    cudaFree(d_y);
    free(A);
    free(csrRowPtrA);
    free(csrColIndA);
    free(csrValA);
    free(x);
    free(y);

    return 0;
}
