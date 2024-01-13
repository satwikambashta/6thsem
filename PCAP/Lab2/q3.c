// MPI program to read N elements of array in root process where N is equal to the total number of processes

#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int arr[size];
    int val=0;
    char buffer[size * sizeof(int) + MPI_BSEND_OVERHEAD];
    MPI_Status status;
    MPI_Buffer_attach(buffer, size * sizeof(int) + MPI_BSEND_OVERHEAD);
    if (rank == 0)
    {

        for (int i = 0; i < size; i++)
        {
            printf("Enter element arr[%d]", i);
            scanf("%d", &arr[i]);
            // fflush(stdout);
        }
        for (int i = 0; i < size; i++)
            MPI_Bsend(&arr[i], 1, MPI_INT, i, 1, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&val, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

        if (rank % 2 == 0)
        {
            printf("EVEN\tRank: %d, Num: %d, Square: %d \n", rank, val, val * val);
        }
        else
        {
            printf("ODD\tRank: %d, Num: %d, Cube: %d\n", rank, val, val * val * val);
        }
    }
    MPI_Buffer_detach(&buffer, &size);
    MPI_Finalize();
    return 0;
}