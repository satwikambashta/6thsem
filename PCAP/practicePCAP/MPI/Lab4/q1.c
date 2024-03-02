//Write an MPI program unsing N processes to find 1!+2!+....N!. Use scann. Handle different errors. use mpierrhandlerset Use collective communication.


#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char* argv[])
{
    int rank,size,fact=1,factsum,i,error_code;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    for(i=1; i<=rank+1; i++)
        fact= fact*i;
    
    printf("\nRank: %d produced factorial: %d",rank,fact);

    error_code = MPI_Scan(&fact, &factsum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    ErrorHadler(error_code);

    if(rank==size-1)
        printf("\nSum of all factorials: %d", factsum);
   
    MPI_Finalize();
    exit(0);
}