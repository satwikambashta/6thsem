#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char* argv[])
{
    int rank, size, count=0 ,temp1;
    char str1[50], temp[50];
    char arr[50];int strLen;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0)
    {
        printf("Enter string: ");
        scanf("%99[^\n\t]", str1);
        printf("Entered string is : %s", str1);
        
        printf("\nENter size of each word: ");
        scanf("%d", &strLen);
        strLen++;
    }

    MPI_Bcast(&strLen, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(str1, strLen, MPI_CHAR, temp, strLen, MPI_CHAR, 0, MPI_COMM_WORLD);
    printf("Process: %d has received %s\n", rank, temp);

    for (int i = 0, j = strLen - 2; i <= j; i++, j--) {
        char c = temp[i];
        temp[i] = temp[j];
        temp[j] = c;
    }

    MPI_Gather(temp, strLen, MPI_CHAR, arr, strLen, MPI_CHAR, 0, MPI_COMM_WORLD);
    if(rank==0)
    {
        printf("\n\n%s\n\n",arr);
    }
    
    MPI_Finalize();
    return 0;
}