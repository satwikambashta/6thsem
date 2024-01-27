//N PROCESSES FIND 1!+2!+..+N!. Use collective communication

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int rank,size,fact=1,factsum,i;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Errhandler_set(MPI_COMM_WORLD)
    for(i=1; i<=rank+1; i++)
    {
        fact*=i;
    }
    MPI_Reduce(&fact, &factsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank==0)
        printf("Sum of all factorials: %d", factsum);

    MPI_Finalize();
    exit(0);
}