#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>

int fact(int num)
{
    int fat=1;
    while(num>0)
    {
        fat=fat*num;
        num--;
    }
    return fat;
}
int main(int argc, char* argv[])
{
    int rank, size, num;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    int arr[size];
    int buf[size];
    if(rank==0)
    {
        printf("Enter %d values", size);
        for(int i=0 ;i<size; i++)
        {
            scanf("%d", &arr[i]);
        }
    }
        MPI_Scatter(arr, 1, MPI_INT, &num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Number received at process %d is %d \n", rank, num);
    num=fact(num);
    MPI_Gather(&num, 1, MPI_INT, buf, 1, MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        for(int i=0; i< size; i++)
        {
            printf("\nprocess %d received value %d from %d",rank, buf[i], i);
        }
    }
    

    MPI_Finalize();
    return 0;
}