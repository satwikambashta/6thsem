#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

    int rank, size, errcode, rectangleCount = 100000, leftLimit = 0, rightLimit = 1;
    double rectangle_width = (double) (rightLimit - leftLimit) / rectangleCount, ans;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    int rectanglesPerProcess = rectangleCount / size;

    double x_left = leftLimit + rank * rectanglesPerProcess * rectangle_width, sum = 0;
    for (int i = 0; i < rectanglesPerProcess; i++) {
        double x_rectangle_left = (double) x_left + i * rectangle_width;
        double x_rectangle_mid = (double) x_rectangle_left + (rectangle_width / 2);
        double rectangle_height = (double) 4 / (1 + x_rectangle_mid * x_rectangle_mid);
        sum += rectangle_height * rectangle_width;
    }
    
    printf("Process with rank %d sending: %2f\n", rank, sum);

    errcode = MPI_Reduce(&sum, &ans, 1, MPI_DOUBLE, MPI_SUM, 0,MPI_COMM_WORLD);
    errorHadler(errcode);

    if (rank == 0) 
        printf("Final approximation of pi: %2f\n", ans);
    
    MPI_Finalize();
    return 0;
}