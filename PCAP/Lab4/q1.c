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
    // Create an error handler
    // MPI_Errhandler errhandler;
    // MPI_Comm_create_errhandler(ErrorHadler, &errhandler);
    // Set the error handler for the communicator
    // MPI_Errhandler_set(MPI_COMM_WORLD, errhandler);
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    for(i=1; i<=rank+1; i++)
        fact*=i;
    // MPI_Bcast(&fact, 1, MPI_INT, 4, MPI_COMM_WORLD);
    MPI_Send(&fact,1,MPI_INT,size,0,MPI_COMM_WORLD);
    MPI_Scan(&fact, &factsum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    if(rank==size-1)
        printf("Sum of all factorials: %d", factsum);
    // if(rank==size)
    {
        // MPI_Comm_call_errhandler(MPI_COMM_WORLD, 3);
        error_code = MPI_Comm_size(3, &size);
        ErrorHadler(error_code);
    }
    MPI_Finalize();
    exit(0);
}