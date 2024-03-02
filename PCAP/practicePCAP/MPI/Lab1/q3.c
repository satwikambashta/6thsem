#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);
    int arg1= atoi(argv[1]);
    int arg2= atoi(argv[2]);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    switch(rank){
        case 0:
            printf("Rank:%d Sum: %d", rank, (arg1+arg2));
            break;
        case 1:
            printf("Rank:%d Product: %d", rank, (arg1*arg2));
            break;
        case 2:
            printf("Rank:%d Difference: %d", rank, (arg1-arg2));
            break;
        case 3:
            printf("Rank:%d Divident: %d", rank, (arg1/arg2));
            break;

    }

    MPI_Finalize();
}