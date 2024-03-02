#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int m;
    int arr[100] = {0};
    float B[100];
    int temp[100] = {0};
    if (rank == 0)
    {
        printf("Enter number of elements: ");
        scanf("%d", &m);

        int r = m * size;

        printf("Enter %d number of elements:", r);
        for (int i = 0; i < r; i++)
            scanf("%d", &arr[i]);

        printf("\nEntered elements are: \n");
        for (int i = 0; i < r; i++)
            printf("%d\t", arr[i]);
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    float sum = 0; // Changed from double to float

    MPI_Scatter(arr, m, MPI_INT, temp, m, MPI_INT, 0, MPI_COMM_WORLD);
    
    for (int i = 0; i < m; i++)
    {
        printf("\nReceived element %d at process %d\n", temp[i], rank);
        sum += temp[i];
    }

    sum = sum / m;

    printf("\nCalculated average at rank %d is %f", rank, sum);
    
    MPI_Gather(&sum, 1, MPI_FLOAT, B, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    if (rank == 0)
    {
        printf("\nValues received at the root process: \n");
        for (int i = 0; i < m; i++)
            printf("\t%f", B[i]);
    }
    MPI_Finalize();
    return 0;
}