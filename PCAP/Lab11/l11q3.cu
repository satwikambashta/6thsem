// write a program in cuda to perform tiled 1d convolution 
// operation on the input array N of size width using the mask array ,  M of size mask_width, to produce the resultant array P of size width. 

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define BLOCK_SIZE 256

__global__ void tiledConvolution1D(float *N, float *M, float *P, int width, int mask_width, int padding) {
 
  __shared__ float s_Mask[BLOCK_SIZE];

  int idx = threadIdx.x + blockIdx.x * blockDim.x;
  int i = idx + padding; 

  if (threadIdx.x < mask_width) {
    s_Mask[threadIdx.x] = M[threadIdx.x];
  }
  __syncthreads();

  if (i < width + padding) {
    float sum = 0;
    for (int j = 0; j < mask_width; j++) {
      int inputIndex = i - j;
      if (inputIndex >= 0) {
        sum += N[inputIndex] * s_Mask[j];
      }
    }
    P[idx] = sum;
  }
}

int main() {
  int width = 1024; /
  int mask_width = 5;
  int padding = mask_width / 2;

  float *h_N = (float*)malloc((width + 2 * padding) * sizeof(float));
  float *h_M = (float*)malloc(mask_width * sizeof(float));
  float *h_P = (float*)malloc(width * sizeof(float));

  for (int i = 0; i < width; i++) {
    h_N[i + padding] = rand() / (float)RAND_MAX; 
  }
  for (int i = 0; i < mask_width; i++) {
    h_M[i] = rand() / (float)RAND_MAX;
  }

  float *d_N, *d_M, *d_P;
  cudaMalloc((void**)&d_N, (width + 2 * padding) * sizeof(float)); 
  cudaMalloc((void**)&d_M, mask_width * sizeof(float));
  cudaMalloc((void**)&d_P, width * sizeof(float));

  cudaMemcpy(d_N, h_N, (width + 2 * padding) * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(d_M, h_M, mask_width * sizeof(float), cudaMemcpyHostToDevice);

  int blockSize = BLOCK_SIZE;
  int gridSize = (width + blockSize - 1) / blockSize;

  tiledConvolution1D<<<gridSize, blockSize>>>(d_N, d_M, d_P, width, mask_width, padding);

  cudaMemcpy(h_P, d_P, width * sizeof(float), cudaMemcpyDeviceToHost);

  printf("Final Output Matrix:\n");
  for (int i = 0; i < width; i++) {
    printf("%f ", h_P[i]);
  }
  printf("\n");

  free(h_N);
  free(h_M);
  free(h_P);
  cudaFree(d_N);
  cudaFree(d_M);
  cudaFree(d_P);

  return 0;
}
