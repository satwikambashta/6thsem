#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int rank,size,len;
    char str1[50], str2[50];
    char temp1[20], temp2[20], combstring[60], finalstring[69];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank==0)
    {
        printf("ENter string1: ");
        scanf("%s", str1);
        printf("Enter string2: ");
        scanf("%s",str2);
    }
    len=strlen(str1)/size;
    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(str1, len, MPI_CHAR, temp1, len, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(str2, len, MPI_CHAR, temp2, len, MPI_CHAR, 0, MPI_COMM_WORLD);
    for(int i=0,j=0; i<len; i++, j=j+2)
    {
        combstring[j] = temp1[i];
        combstring[j+1] = temp2[i];
    }
    len*=2;
    MPI_Gather(combstring, len, MPI_CHAR, finalstring, len, MPI_CHAR, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("\n\ncombined string is: %s \n\n", finalstring);
    MPI_Finalize();
    return 0;
}