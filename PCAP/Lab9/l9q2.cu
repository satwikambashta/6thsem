//multiply two matrices for specifications
//a)each rowof resultant matrix to be computed by one thread
//b)each column if resultantmatrix is to be computed by one thread
//c)each element of resultant matrix to be computed by one thread

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void multiplyMatricesRow(int *a, int *b, int *c, int m, int n, int p)
{
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < m) {
        for (int col = 0; col < p; col++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += a[row * n + k] * b[k * p + col];
            }
            c[row * p + col] = sum;
        }
    }
}

__global__ void multiplyMatricesColumn(int *a, int *b, int *c, int m, int n, int p)
{
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (col < p) {
        for (int row = 0; row < m; row++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += a[row * n + k] * b[k * p + col];
            }
            c[row * p + col] = sum;
        }
    }
}

__global__ void multiplyMatricesElement(int *a, int *b, int *c, int m, int n, int p)
{
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    int col = blockIdx.y * blockDim.y + threadIdx.y;
    if (row < m && col < p) {
        int sum = 0;
        for (int k = 0; k < n; k++) {
            sum += a[row * n + k] * b[k * p + col];
        }
        c[row * p + col] = sum;
    }
}

int main(void)
{
    int m, n, p;
    printf("Enter the value of m: ");
    scanf("%d", &m);
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Enter the value of p: ");
    scanf("%d", &p);

    int sizeA = m * n;
    int sizeB = n * p;
    int sizeC = m * p;

    int *a = (int *)malloc(sizeA * sizeof(int));
    int *b = (int *)malloc(sizeB * sizeof(int));
    int *c = (int *)malloc(sizeC * sizeof(int));

    printf("Enter matrix A (%d x %d):\n", m, n);
    for (int i = 0; i < sizeA; i++)
        scanf("%d", &a[i]);

    printf("Enter matrix B (%d x %d):\n", n, p);
    for (int i = 0; i < sizeB; i++)
        scanf("%d", &b[i]);

    int *d_a, *d_b, *d_c;
    cudaMalloc((void **)&d_a, sizeA * sizeof(int));
    cudaMalloc((void **)&d_b, sizeB * sizeof(int));
    cudaMalloc((void **)&d_c, sizeC * sizeof(int));

    cudaMemcpy(d_a, a, sizeA * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, sizeB * sizeof(int), cudaMemcpyHostToDevice);

    int choice;
    printf("Choose the approach (1: Row-wise, 2: Column-wise, 3: Element-wise): ");
    scanf("%d", &choice);

    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((p + threadsPerBlock.x - 1) / threadsPerBlock.x, (m + threadsPerBlock.y - 1) / threadsPerBlock.y);

    switch (choice) {
        case 1:
            multiplyMatricesRow<<<numBlocks, threadsPerBlock>>>(d_a, d_b, d_c, m, n, p);
            break;
        case 2:
            multiplyMatricesColumn<<<numBlocks, threadsPerBlock>>>(d_a, d_b, d_c, m, n, p);
            break;
        case 3:
            multiplyMatricesElement<<<numBlocks, threadsPerBlock>>>(d_a, d_b, d_c, m, n, p);
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }

    cudaMemcpy(c, d_c, sizeC * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Result matrix is:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%d\t", c[i * p + j]);
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
