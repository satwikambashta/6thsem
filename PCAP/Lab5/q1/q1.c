//Write an Opencl program which takes N integers as input. IIt converts these integers intp their 
//corresponding octal values and stores the result in another array in parallel


#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>
#define MAX_SOURCE_SIZE (0x100000) //Max source size of kernel string 

int main(void){
	//Create 2 input vectors  
	int i; 
	int LIST_SIZE; 
	printf("Enter how many elements: "); 
	scanf("%d", &LIST_SIZE); 

	//initialize input vectors 
	int *A = (int*)malloc(sizeof(int)*LIST_SIZE); 
	printf("Enter %d elements: \n", LIST_SIZE); 
	for(i = 0; i<LIST_SIZE; i++){
		scanf("%d",&A[i]); 
	}

	//load the kernel 
	FILE *fp; 
	char *source_str; 
	size_t source_size; 
	fp = fopen("vectorCL.cl", "r"); 
	if(!fp){
		fprintf(stderr, "Failed to load kernel. \n"); 
		getchar(); 
		exit(1); 
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE); 
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp); 
	fclose(fp); 

	cl_platform_id platform_id = NULL; 
	cl_device_id device_id = NULL; 
	cl_uint ret_num_devices; 
	cl_uint ret_num_platforms; 
	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms); 
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices); 
	
	//creaTE OPENCL CONTEXT
	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret); 

	//CREATE COMMAND QUEUE
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret); 

	//CREATE MEMORY BUFFERS
	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE*sizeof(int), NULL, &ret); 
	// cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE*sizeof(int), NULL, &ret); 
	cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE*sizeof(int), NULL, &ret); 
	//COPY THE LISTS a AND B TO RESPECTIVEMEMORY BUFFERS
	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE*sizeof(int), A, 0, NULL, NULL); 
	// ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, LIST_SIZE*sizeof(int), B, 0, NULL, NULL); 

	//CREATE PRGM FROM KERNEL SOURCE
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t)&source_size, &ret); 

	//BUILD THE PRGM
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL); 

	// /CREATE OPENCL KERNEL OBJECT
	cl_kernel kernel = clCreateKernel(program, "vector_add", &ret); 

	///SET ARGUMENTS OF KERNEL
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj); 	
	// ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj); 	
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&c_mem_obj); 	

	//EXECUTE OPENCL kERNEL ON THE ARRAY
	size_t global_item_size = LIST_SIZE; 
	size_t local_item_size = 1; 

	cl_event event; 
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL); 
	ret = clFinish(command_queue); 
	//read the memory buffer C on the device to the local variable C
	int *C = (int*)malloc(sizeof(int)*LIST_SIZE); 
	ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, LIST_SIZE *sizeof(int), C, 0, NULL, NULL); 
	
	//display result to the screen
	for(i = 0; i<LIST_SIZE; i++)
		printf("%d in oct = %d\n", A[i], C[i]); 
	// for(i = 0; i<LIST_SIZE; i++)
	// 		printf("%d\n", C[i]); 
	//clean up
	ret = clFlush(command_queue); 
	ret = clReleaseKernel(kernel); 
	ret = clReleaseProgram(program); 
	ret = clReleaseMemObject(a_mem_obj); 
	// ret = clReleaseMemObject(b_mem_obj); 
	ret = clReleaseMemObject(c_mem_obj); 
	ret = clReleaseCommandQueue(command_queue); 
	ret = clReleaseContext(context); 

	

	free(A); 
	// free(B); 
	free(C); 
	getchar(); 
	return 0; 
}
