//4x4 matrix and display output using 4 processes


#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void ErrorHadler(int error_code) {
    if (error_code != MPI_SUCCESS)
    {
        char error_string[BUFSIZ];
        int length_of_error_string, error_class;

        MPI_Error_class(error_code, &error_class);
        MPI_Error_string(error_code, error_string, &length_of_error_string);
        printf("%d %s\n", error_code, error_string);
    }
}

int main(int argc, char *argv[]) {
    int rank, size,error_code, mat[3][3], *array, ele, count, comcount;
    float answer,sum;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    error_code = MPI_Comm_size(3, &size);
    ErrorHadler(error_code);
    count=0;
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
    }
    array = (int *)calloc(4, sizeof(int));
    MPI_Scatter(mat, 4, MPI_INT, array, 4, MPI_INT, 0, MPI_COMM_WORLD);
    
    MPI_Finalize();
    return 0;
}