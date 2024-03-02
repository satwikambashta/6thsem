#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char* argv[])
{
    int rank, size, count=0;
    char str1[50], temp[50];
    int arr[20];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0)
    {
        printf("Enter string: ");
        scanf("%s", str1);
        printf("Entered string is : %s", str1);

    }
    int strLen=strlen(str1)/size;

    MPI_Bcast(&strLen, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(str1, strLen, MPI_CHAR, temp, strLen, MPI_CHAR, 0, MPI_COMM_WORLD);
    printf("Process: %d has received %s\n", rank, temp);
    for(int i=0; i<strLen;i++)
    {
        if (temp[i] != 'a' && temp[i] != 'e' && temp[i] != 'i' && temp[i] != 'o' && temp[i] != 'u')
            count++;
    }
    MPI_Gather(&count, 1, MPI_INT, arr, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank==0)
    for(int i=0; i<size; i++)
    {
        printf("Rank %d has %d non vowels\t", i, arr[i]);
    }
    MPI_Finalize();
    return 0;
}