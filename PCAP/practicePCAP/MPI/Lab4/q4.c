#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    int rank, size, num, count = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int arr[4][4];
    if (rank == 0)
    {
        printf("Enter matrix 16 elements: \n");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                scanf("%d", &arr[i][j]);
            }
        }
        printf("Entered matrix:\n");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        }
    }
    int row[4], ans[4];

    MPI_Scatter(arr, 4, MPI_INT, row, 4, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scan(row, ans, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    MPI_Gather(ans, 4, MPI_INT, arr, 4, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Output matrix:\n");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                printf("%d ", arr[i][j]);
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}