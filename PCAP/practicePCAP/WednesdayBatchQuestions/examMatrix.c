#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int mat[4][4], tri[4];
    int arr[50], transpose[4][4];
    int partArr[10];
    int arrSol[10], matSol[10];
    int n;
    int sumMin[10];
    int mini=1000, maxi=-100;
    if(rank==0)
    {
        printf("Enter  the elements of matrix:\n");
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
                scanf("%d", &mat[i][j]);
        }
        printf("Enter number of elements in the array: ");
        scanf("%d", &n);
        printf("Enter elements of the array: ");
        for(int i=0; i<n; i++)
        {
            scanf("%d", &arr[i]);
        }
        printf("\n\nThe matrix is :\n");
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
                printf("%d \t", mat[i][j]);
            printf("\n");
        }

        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
                transpose[j][i]=mat[i][j];
        }

        printf("\nthe array is: \n");
        for(int i=0; i<n; i++)
            printf("%d \t", arr[i]);

    }
    int p=n/size;
    MPI_Bcast(&p, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr, p, MPI_INT, partArr, p, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(transpose, 4, MPI_INT, tri, 4, MPI_INT, 0, MPI_COMM_WORLD);
    printf("\n");
    for(int i=0; i<p; i++)
    {
        printf("Process %d received %d \t",rank,partArr[i]);
    }
    printf("\n");
    mini=1000;
    maxi=-1000;
    for(int i=0; i<p; i++)
    {
        if(mini>partArr[i])
            mini=partArr[i];
    }
    printf("\n\nMinimum element from process %d is %d\n", rank, mini);
    for(int i=0; i<4; i++)
    {
        if(maxi<tri[i])
            maxi=tri[i];
    }
    printf("\n\nMaximum element from process %d is %d\n", rank, maxi);

    printf("sum from process %d is %d", rank, mini+maxi);
    // MPI_Reduce(&mini)
    // if(rank==0)
    // {


    //     printf("\n\nSUM:\n");
    //     for(int i=0; i<4; i++)
    //     {
    //         printf("%d \t", sumMin[i]);
    //     } 

    // }

    MPI_Finalize();
    
    return 0;
}