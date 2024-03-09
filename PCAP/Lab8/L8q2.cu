/* write a cuda program to read string s and produce string rs.
sample input S: PCAP .sample output RS:PCAPPCAPCP*/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

__global__ void GenerateRS(char *S, char *RS, int length)
{
    int i = threadIdx.x;
    if (i < length) {
        // Copy each character from S to RS
        RS[i] = S[i];
    }
    // Append "CP" at the end of the string
    if (i == length - 1) {
        RS[length] = S[0]; // Append the first character of S again
        RS[length + 1] = 'C';
        RS[length + 2] = 'A'; // Append 'A' after 'C'
        RS[length + 3] = 'P'; // Append 'P' after 'A'
        RS[length + 4] = 'C'; // Append 'C' after 'P'
        RS[length + 5] = 'P'; // Append 'P' after 'C'
        RS[length + 6] = '\0'; // Null-terminate the string
    }
}

int main()
{
    char S[N] = "PCAP";
    char *d_S, *d_RS;
    char RS[N * N];

    int length = strlen(S);

    cudaMalloc((void **)&d_S, length * sizeof(char));
    cudaMalloc((void **)&d_RS, (length + 6) * sizeof(char));

    cudaMemcpy(d_S, S, length * sizeof(char), cudaMemcpyHostToDevice);

    GenerateRS<<<1, length + 6>>>(d_S, d_RS, length);

    cudaMemcpy(RS, d_RS, (length + 6) * sizeof(char), cudaMemcpyDeviceToHost);

    printf("Input string S: %s\n", S);
    printf("Output string RS: %s\n", RS);

    cudaFree(d_S);
    cudaFree(d_RS);

    return 0;
}
