#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void errorHadler(int error_code) {
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

    int rank, size, num, count = 0, ans, errcode;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    int arr[3][3];
    if (rank == 0) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("\nEnter a[%d][%d] ", i, j);
                scanf("%d", &arr[i][j]);
            }
        }
        printf("Enter number to search for:");
        scanf("%d", &num);
    }
    int row[3];

    MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    errcode = MPI_Scatter(arr, 3, MPI_INT, row, 3, MPI_INT, 0, MPI_COMM_WORLD);
    errorHadler(errcode);

    for (int i = 0; i < 3; i++) {
        if (row[i] == num)
            count++;
    }

    printf("Process with rank %d sending: %d\n", rank, count);

    errcode = MPI_Scan(&count, &ans, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    errorHadler(errcode);

    if (rank == size - 1) {
        printf("Total number of occurences: %d", ans);
    }
    
    MPI_Finalize();
    return 0;
}