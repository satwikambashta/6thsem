/* count number of times a given word is repeated in a sentence*/

##include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

__global__ void CUDACount(char *A, unsigned int *d_count, char *word, int wordLength)
{
    int i = threadIdx.x;
    int j;
    for (j = 0; j < wordLength; j++) {
        if (A[i + j] != word[j]) {
            break;
        }
    }
    if (j == wordLength) {
        atomicAdd(d_count, 1);
    }
}

int main()
{
    char A[N];
    char *d_A;
    unsigned int count = 0, *d_count;
    char word[N]; // Buffer to store the word to search for

    printf("Enter a string: ");
    if (scanf("%99[^\n\t]", A) != 1) {
        printf("Failed to read the string.\n");
        return 1; // Return an error code
    }

    // Clear the input buffer to remove the newline character left by the previous scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter a word to search for: ");
    if (scanf(" %99[^\n\t]", word) != 1) { // Note the space before the format specifier
        printf("Failed to read the word.\n");
        return 1; // Return an error code
    }

    int wordLength = strlen(word);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

    cudaMalloc((void **)&d_A, strlen(A) * sizeof(char));
    cudaMalloc((void **)&d_count, sizeof(unsigned int));

    cudaMemcpy(d_A, A, strlen(A) * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &count, sizeof(unsigned int), cudaMemcpyHostToDevice); // Pass the address of count

    cudaError_t error = cudaGetLastError();
    if (error != cudaSuccess)
    {
        printf("CUDA Error1: %s\n", cudaGetErrorString(error));
    }

    // Allocate memory for the word on the device
    char *d_word;
    cudaMalloc((void **)&d_word, wordLength * sizeof(char));
    cudaMemcpy(d_word, word, wordLength * sizeof(char), cudaMemcpyHostToDevice);

    // Launch the kernel with the word and its length
    CUDACount<<<1, strlen(A)>>>(d_A, d_count, d_word, wordLength);

    error = cudaGetLastError();
    if (error != cudaSuccess)
    {
        printf("CUDA Error2: %s\n", cudaGetErrorString(error));
    }

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    float elapsedTime;
    cudaEventElapsedTime(&elapsedTime, start, stop);

    cudaMemcpy(&count, d_count, sizeof(unsigned int), cudaMemcpyDeviceToHost); // Copy back the result

    printf("Total occurrences of '%s' = %d\n", word, count);
    printf("Time Taken = %f ms\n", elapsedTime);

    cudaFree(d_A);
    cudaFree(d_count);
    cudaFree(d_word); // Free the memory allocated for the word on the device

    return 0;
}
