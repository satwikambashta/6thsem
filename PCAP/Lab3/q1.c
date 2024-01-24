// read n values from the root process. it sends one number to each process. each process receives and finds factorialof the number and returns
//rooot gathers these and fins the sum

#include "mpi.h"
#include <stdio.h>

int factorial(int a)
{
    int fact=1;
    if(a==1 || a==0)
    {
        return 1;
    }
    else{
        while(a>0)
        {
           fact*=a; 
           a--;
        }
        
    }
}

int main(int argc, char* argv[])
{
    int rank, size, N, A[10], B[10], c,i;
    int sum=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0)
    {
        N=size;
        fprintf(stdout, "Enter %d values: \n",N);
        fflush(stdout);
        for(i=0; i<N; i++)
            scanf("%d", &A[i]);
    }
    MPI_Scatter(A, 1, MPI_INT,&c, 1, MPI_INT, 0, MPI_COMM_WORLD);
    fprintf(stdout, "I ahve received %d in procesws %d\n", c,rank);
    fflush(stdout);
    c=factorial(c);
    MPI_Gather(&c, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank==0)
    {
        fprintf(stdout, "The result gathered in the root\n");
        fflush(stdout);
        for(i=0; i<N; i++)
        {
            fprintf(stdout,"%d \t", B[i]);
            sum+=B[i];
        }
        fprintf(stdout, "The sum is %d \n",sum);
        
        fflush(stdout);
    }


    MPI_Finalize();
    return 0;
}