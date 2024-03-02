#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <string.h>


int main(int argc, char* argv[])
{
    int rank, size;
    char toggleThis[] = "Hello";

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(toggleThis[rank]>='a' && toggleThis[rank]<='z')
    {
        toggleThis[rank]-=32;
    }
    else if(toggleThis[rank]>='A'){
        toggleThis[rank]+=32;
    }
    printf("%s", toggleThis);
    MPI_Finalize();
    return 0;
}