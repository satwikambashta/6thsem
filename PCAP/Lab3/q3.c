// read a string. n processes. find number of non vowels, print number of non vovels found by each process in the root process.
// print total number of non vowels.

#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argv, char *argc[])
{
    int rank, size, result, length;
    int B[10];

    MPI_Init(&argv, &argc);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char string[64], *str;
    if (rank == 0)
    {
        printf("Enter the string:");
        scanf("%s", string);
        length = strlen(string);
        length /= size;
    }

    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);
    str = (char *)calloc(length, sizeof(char));
    MPI_Scatter(string, length, MPI_CHAR, str, length, MPI_CHAR, 0, MPI_COMM_WORLD);
    int sendResult = 0;
    for (int i = 0; i < length; i++)
    {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' || str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U')
            continue;    
        sendResult++;
    }
    MPI_Gather(&sendResult, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        for(int i=0; i<size; i++)
        {
            printf("Rank: %d had %d non-vowels", i, B[i]);
        }
        printf("The total non-vowels are : %d\n", result);
    }
    
    // printf("Process %d found %d non vowels\n", rank, sendResult);
    // MPI_Reduce(&sendResult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // if (rank == 0)
    // {
    //     printf("The total non-vowels are : %d\n", result);
    // }
    
        
    free(str);
    MPI_Finalize();
    return 0;
}
