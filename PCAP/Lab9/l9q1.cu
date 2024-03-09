//add two matrices by 
//a)each rowof resultant matrix to be computed by one thread
//b)each column if resultantmatrix is to be computed by one thread
//c)each element of resultant matrix to be computed by one thread

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void addMatricesRow(int *a, int *b, int *c, int m, int n)
{
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < m) {
        for (int col = 0; col < n; col++) {
            c[row * n + col] = a[row * n + col] + b[row * n + col];
        }
    }
}

__global__ void addMatricesColumn(int *a, int *b, int *c, int m, int n)
{
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (col < n) {
        for (int row = 0; row < m; row++) {
            c[row * n + col] = a[row * n + col] + b[row * n + col];
        }
    }
}

__global__ void addMatricesElement(int *a, int *b, int *c, int m, int n)
{
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    int col = blockIdx.y * blockDim.y + threadIdx.y;
    if (row < m && col < n) {
        c[row * n + col] = a[row * n + col] + b[row * n + col];
    }
}

int main(void)
{
    int m, n;
    printf("Enter the value of m: ");
    scanf("%d", &m);
    printf("Enter the value of n: ");
    scanf("%d", &n);

    int size = m * n;
    int *a = (int *)malloc(size * sizeof(int));
    int *b = (int *)malloc(size * sizeof(int));
    int *c = (int *)malloc(size * sizeof(int));

    printf("Enter matrix A:\n");
    for (int i = 0; i < size; i++)
        scanf("%d", &a[i]);

    printf("Enter matrix B:\n");
    for (int i = 0; i < size; i++)
        scanf("%d", &b[i]);

    int *d_a, *d_b, *d_c;
    cudaMalloc((void **)&d_a, size * sizeof(int));
    cudaMalloc((void **)&d_b, size * sizeof(int));
    cudaMalloc((void **)&d_c, size * sizeof(int));

    cudaMemcpy(d_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size * sizeof(int), cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((n + threadsPerBlock.x - 1) / threadsPerBlock.x, (m + threadsPerBlock.y - 1) / threadsPerBlock.y);
    
    int choice;
    printf("Enter 1 for rowwise, 2 for columnwise, 3 for elementwise: ");
    scanf("%d", &choice);
    switch(choice){
        case 1: 
            printf("ROW wISE: \n");
            addMatricesRow<<<numBlocks, threadsPerBlock>>>(d_a, d_b, d_c, m, n);
            break;
        case 2: 
            printf("COLUMN WISE; \n");
            addMatricesColumn<<<numBlocks, threadsPerBlock>>>(d_a, d_b, d_c, m, n);
            break;
        case 3: 
            addMatricesElement<<<numBlocks, threadsPerBlock>>>(d_a, d_b, d_c, m, n);
            break;
        default:
            printf("Incorrect input. defaulting to elemenmtwise\n");
    }

    cudaMemcpy(c, d_c, size * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Result matrix is:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", c[i * n + j]);
        }
        printf("\n");
    }

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(a);
    free(b);
    free(c);

    return 0;
}
