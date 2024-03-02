#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{
    int rank, size;
    int c=3;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("My rank is %d and the answer is: %f", rank, pow(rank,c));
    MPI_Finalize();
    return 0;
}