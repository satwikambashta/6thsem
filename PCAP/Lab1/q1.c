//find pow(x,rank) where x is the integer constant and rank is the rank of the process

#include "mpi.h"
#include <stdio.h>
#include <math.h>
int main(int argc, char* argv[])
{
   int rank, size;
   int x=3;
   printf("X is %d\n",x);
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   printf("My rank is %d in total %d processes\n", rank, size);
   printf("x^rank: %f \n", pow(x,rank));
   MPI_Finalize();
   return 0; 
}