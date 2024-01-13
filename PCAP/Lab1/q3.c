#include "mpi.h"
#include <stdio.h>



int main(int argc, char* argv[])
{
   int rank;
   int a= atoi(argv[1]);
   int b= atoi(argv[2]);
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   switch(rank)
   {
    case 0:
        printf("RANK: %d %d+%d: %d\n", rank,a,b, (a+b));
        break;
    case 1:
        printf("RANK: %d %d-%d: %d\n", rank,a,b, (a-b));
        break;
    case 2:
        printf("RANK: %d %dx%d: %d\n", rank,a,b, (a*b));
        break;
    case 3:
        printf("RANK: %d %d/%d= %d\n", rank,a,b, (a/b));
        break;
    default:
        printf("Too many processes. need only 4");
        break;
   }
   MPI_Finalize();
   return 0; 
}