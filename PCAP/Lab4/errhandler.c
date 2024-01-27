#include "mpi.h"
#include <stdio.h>

void ErrorHadler(int error_code)
{

    if (error_code != MPI_SUCCESS)
    {
        char error_string[BUFSIZ];
        int length_of_error_string, error_class;
        MPI_Error_class(error_code, &error_class);
        MPI_Error_string(error_code, error_string, &length_of_error_string);
        printf("%d %s\n", error_code, error_string);

        MPI_Error_string(error_class, error_string, &length_of_error_string);
        printf("%d %s\n", error_class, error_string);
    }
}

int main(int argc, char *argv[])
{
    int C = 3;
    int numtasks, rank, len, error_code;
    MPI_Init(&argc, &argv);
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    error_code = MPI_Comm_size(C, &numtasks);
    ErrorHadler(error_code);
    printf("Number of tasks= %d My rank= %d \n", numtasks, rank);
    MPI_Finalize();
}