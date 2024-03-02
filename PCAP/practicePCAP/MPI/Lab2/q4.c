#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n;
    if (rank == 0)
    {
        printf("Enter a number: ");
        scanf("%d", &n);
        printf("number is %d \n at process %d", n, rank);
        n++;
        MPI_Ssend(&n, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD);
    }
    else if (rank < size)
    {
        MPI_Recv(&n, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, &status);
        printf("\t Number received is %d at rank %d \n", n, rank);
        n = n + 1;
        if (rank + 1 < size)
        {
            MPI_Ssend(&n, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}