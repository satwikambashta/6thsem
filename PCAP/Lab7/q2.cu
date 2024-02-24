// addd two vectors of length N by keeping the number of threADS PER BLOCK AS 256 AND VARY the number of
//  blocks to handle N elements 

#include<stdio.h>

__global__ void vectorAdd_q2(float *A, float *B,float *C,int n)
{
	int tid=blockIdx.x*blockDim.x+threadIdx.x;

	if(tid<n)
		C[tid]=A[tid]+B[tid];
}

int main(void) 
{
	int n;

	printf("Enter number of elements:\t");
	scanf("%d",&n);

	float *h_A,*h_B,*h_C;
	float *d_A, *d_B, *d_C;
	
	int size = sizeof(float)*n;

	h_A=(float*)malloc(sizeof(size));
	h_B=(float*)malloc(sizeof(size));
	h_C=(float*)malloc(sizeof(size));

	cudaMalloc((void **)&d_A, size);
	cudaMalloc((void **)&d_B, size);
	cudaMalloc((void **)&d_C, size);

	printf("Enter vector 1:\n");
	for(int i=0;i<n;i++)
		scanf("%f",&h_A[i]);

	printf("Enter vector 2:\n");
	for(int i=0;i<n;i++)
		scanf("%f",&h_B[i]);

    printf("\nOriginal array 1: \n");
    for(int i=0;i<n;i++)
		printf("\t %f",h_A[i]);
    printf("\nOriginal array 2: \n");
    for(int i=0;i<n;i++)
		printf("\t %f",h_B[i]);



	cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);
	cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

	printf("Resultant Vector Q1_B:\n");
	for(int i=0;i<n;i++)
		printf("%f\t",h_C[i]);

	printf("\n");

	dim3 dimGrid_q2(ceil(n/256.0),1,1);
	dim3 dimBlock_q2(256,1,1);

	vectorAdd_q2<<<dimGrid_q2,dimBlock_q2>>>(d_A,d_B,d_C,n);
	
	cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

	printf("Resultant Vector Q2:\n");
	for(int i=0;i<n;i++)
		printf("%f\t",h_C[i]);

	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
	return 0;
}
