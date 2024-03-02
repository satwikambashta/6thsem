#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int rank, size;MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    
    if(rank==0)
    {
        printf("enter number:");
        int n;
        scanf("%d",&n);
        for(int i=0; i<size;i++)
            MPI_Send(&n, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
        
    }
    else{
        int n;
        MPI_Recv(&n, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        printf("received %d at process %d", n ,rank);
    }
    
    MPI_Finalize();
    return 0;
}