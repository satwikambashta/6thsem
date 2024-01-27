//3x3 matrix. search for element. find number of occurences.

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
        for(int i=0; i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                // printf("\nMat[%d][%d]: ",i,j);
                scanf("%d",&mat[i][j]);
            }
        }
        printf("Enter lemenet: ");
                scanf("%d", &ele);
    }
    MPI_Bcast(&ele, 1, MPI_INT, 0, MPI_COMM_WORLD);
    array = (int *)calloc(3, sizeof(int));
    MPI_Scatter(mat, 3, MPI_INT, array, 3, MPI_INT, 0, MPI_COMM_WORLD);
    for(int i=0; i<3; i++)
    {
        if(array[i]==ele)
            count++;
        
    }
    MPI_Reduce(&count, &comcount, 1, MPI_INT, MPI_SUM,0 , MPI_COMM_WORLD);
    if(rank==0)
        printf("Total count: %d", comcount);
    
    MPI_Finalize();
    return 0;
}