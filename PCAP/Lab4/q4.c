//4x4 matrix and display output using 4 processes

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size,error_code, mat[3][3], *array;
    float answer,sum;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0)
    {
        printf("Enter matrix: \n");
        for(int i=0; i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                // printf("\nMat[%d][%d]: ",i,j);
                scanf("%d",&mat[i][j]);
            }
        }
        for(int i=1; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
               mat[i][j]+=mat[i-1][j];
            }
        }
    }

    //the question only states to print the output using different processes
    array = (int *)calloc(4, sizeof(int));
    MPI_Scatter(mat, 4, MPI_INT, array, 4, MPI_INT, 0, MPI_COMM_WORLD);
    
    for(int i=0; i<4; i++)
        print("%d\t", array[i]);
    
    
    MPI_Finalize();
    return 0;
}
