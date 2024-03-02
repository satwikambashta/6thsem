#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0)
    {   
        char word[50];
        printf("Enter a word: ");
        scanf("%99[^\t\n]", word);
        int wordLen = strlen(word);
        MPI_Ssend(&wordLen, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Ssend(word, wordLen, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        char received[50]; // Allocate space for the received word
        MPI_Recv(received, wordLen, MPI_CHAR, 1, 1, MPI_COMM_WORLD, &status);
        received[wordLen] = '\0'; // Ensure null-termination
        printf("%s\n", received);
    }
    else{
        int wordLen;
        MPI_Recv(&wordLen, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        char* word = (char*)malloc(sizeof(char) * (wordLen + 1)); // +1 for the null terminator
        MPI_Recv(word, wordLen, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
        word[wordLen] = '\0'; // Ensure null-termination

        printf("The string is: %s\n", word);
        if(word[rank] >= 'a' && word[rank] <= 'z')
        {
            word[rank] -= 32;
        }
        else if(word[rank] >= 'A' && word[rank] <= 'Z')
        {
            word[rank] += 32;
        }
        MPI_Ssend(word, wordLen, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
        free(word); // Free the allocated memory
    }
    
    MPI_Finalize();
    return 0;
}