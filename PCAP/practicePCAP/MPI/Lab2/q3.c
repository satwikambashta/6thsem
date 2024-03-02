#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>

int main(int argc, char*argv[])
{
    int rank,size;
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0)
    {
        int arr[10];
        int n;
        printf("Enter array: ");
        for(int i=0; i<size; i++)
            scanf("%d", &arr[i]);
        int bsize=1024;
        char buffer[bsize];
        MPI_Buffer_attach(buffer, bsize);
        for(int i=0;i<size; i++)
        {
            MPI_Bsend(&arr[i], 1, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
        MPI_Buffer_detach(&buffer,&bsize);

    }
        int a;
        MPI_Recv(&a, 1, MPI_INT, 0,1, MPI_COMM_WORLD, &status);
        printf("I received %d at process %d\n", a, rank);
    

    MPI_Finalize();
    return 0;
}