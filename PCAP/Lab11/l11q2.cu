// write a program in cuda to improve the performance of 1d convolution using constant memory

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define FILTER_SIZE 5
#define BLOCK_SIZE 256

// Convolution kernel
__constant__ float d_Filter[FILTER_SIZE]; 

__global__ void convolution1D(float *d_Input, float *d_Output, int inputSize, int outputSize) {
  int idx = threadIdx.x + blockIdx.x * blockDim.x;
  if (idx < outputSize) {
    float sum = 0;
    for (int i = 0; i < FILTER_SIZE; i++) {
      int inputIndex = idx + i - FILTER_SIZE / 2;
      if (inputIndex >= 0 && inputIndex < inputSize) {
        sum += d_Input[inputIndex] * d_Filter[i];
      }
    }
    d_Output[idx] = sum;
  }
}

int main() {
  int inputSize = 1024; 
  int outputSize = inputSize; 

  float *h_Input = (float*)malloc(inputSize * sizeof(float));
  float *h_Output = (float*)malloc(outputSize * sizeof(float));
  float filter[FILTER_SIZE] = {0.1f, 0.2f, 0.3f, 0.2f, 0.1f}; 

  for (int i = 0; i < inputSize; i++) {
    h_Input[i] = rand() / (float)RAND_MAX;
  }

  float *d_Input, *d_Output;
  cudaMalloc((void**)&d_Input, inputSize * sizeof(float));
  cudaMalloc((void**)&d_Output, outputSize * sizeof(float));

  cudaMemcpy(d_Input, h_Input, inputSize * sizeof(float), cudaMemcpyHostToDevice);

  cudaMemcpyToSymbol(d_Filter, filter, FILTER_SIZE * sizeof(float));

  int gridSize = (outputSize + BLOCK_SIZE - 1) / BLOCK_SIZE;

  convolution1D<<<gridSize, BLOCK_SIZE>>>(d_Input, d_Output, inputSize, outputSize);

  cudaMemcpy(h_Output, d_Output, outputSize * sizeof(float), cudaMemcpyDeviceToHost);

  printf("Final Output Matrix:\n");
  for (int i = 0; i < outputSize; i++) {
    printf("%f ", h_Output[i]);
  }
  printf("\n");

  free(h_Input);
  free(h_Output);
  cudaFree(d_Input);
  cudaFree(d_Output);

  return 0;
}