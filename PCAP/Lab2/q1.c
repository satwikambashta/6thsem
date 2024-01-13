//write an MPI program using synchronous send.send , toggle, send back

#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int rank,size;
    char str[] = {'H','e', 'l', 'l', 'o'};
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    if(rank==0)
    {
        MPI_Ssend(&str, strlen(str)+1, MPI_CHAR, 1,1, MPI_COMM_WORLD);
        fprintf(stdout, "\nI have sent %s from process 0\n",str);
        fflush(stdout);
        MPI_Recv(&str, strlen(str)+1, MPI_CHAR, 1, 2,MPI_COMM_WORLD, &status);
        fprintf(stdout, "\nI have received %s in process 0\n",str);
        fflush(stdout);
    }
    else{
        MPI_Recv(&str, strlen(str)+1, MPI_CHAR, 0, 1,MPI_COMM_WORLD, &status);
        fprintf(stdout, "\nI have received %s in process 1\n",str);
        fflush(stdout);
        for(int i=0; i<5; i++)
        {
            if(str[i]>65 && str[i]<90)
                str[i]+=32;
            else
                str[i]-=32;
        }
        MPI_Ssend(&str, strlen(str)+1, MPI_CHAR, 0,2, MPI_COMM_WORLD);
        fprintf(stdout, "\nToggled . I have sent %s from process 1\n",str);
        fflush(stdout);
    }

    MPI_Finalize();

    return 0;
}