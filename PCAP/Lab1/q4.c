#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
   int rank, size;
   char str[] = {'H','E', 'l', 'l', 'o'};
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   if(str[rank]>65 && str[rank]<90)
   {
    str[rank]+=32;
   }
   else
   {
    str[rank]-=32;
   }
   printf("\n%s",str);
   MPI_Finalize();
   return 0; 
}