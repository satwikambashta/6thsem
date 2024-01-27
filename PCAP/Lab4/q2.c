//integrating 4/(1+x^2). divide area under curve into rectangles and distribute. handle different errors

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

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

int main(int argc, char *argv[]) {
    int rank, size,error_code,num_of_parts=0;
    float answer,sum;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    // MPI_Errhandler errhandler;
    // MPI_Comm_create_errhandler(my_error_handler, &errhandler);
    // MPI_Comm_set_errhandler(MPI_COMM_WORLD, errhandler);
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    error_code = MPI_Comm_size(3, &size);
    ErrorHadler(error_code);
    // if(rank==0)
    // {
    //     printf("Enter number of divisions(more for better accuracy):");
    //     scanf("%d",&num_of_parts);
    // }
    // float part=1/num_of_parts;
    
    // for(float i = rank;i <rank+1;i+=part){
    //     sum+=func(i);
    // }
    
    for(float i = rank;i <rank+1;i+=0.0001)
        sum+=4/(1 + i*i);
    
    // sum/=num_of_parts;
    sum/=10000;
    MPI_Reduce(&sum,&answer,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
    if (rank == 0) 
        printf("Value of pi is %f\n", answer);
    
    MPI_Finalize();
    return 0;
}