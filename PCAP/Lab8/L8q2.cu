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
    for (int j = 0; j < length; j++)
    {
        RS[i * length + j] = S[i];
    }
}

int main()
{
    char S[N] = "PCAP";
    char RS[N * N]; // Assuming maximum length for RS

    int length = strlen(S);

    cudaMalloc((void **)&RS, length * length * sizeof(char));

    GenerateRS<<<1, length>>>(S, RS, length);

    cudaMemcpy(RS, RS, length * length * sizeof(char), cudaMemcpyDeviceToHost);

    printf("Input string S: %s\n", S);
    printf("Output string RS: %s\n", RS);

    cudaFree(RS);

    return 0;
}
