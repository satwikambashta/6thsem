// read an integer M and NXM elements into an 1d array in the root process. N is the number of processes
// root sends M elements to each process. they find averafes and sends those back to the root and it calculkates
//  the total average
#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argv, char *argc[]){
	int rank, size, *numbers, *array, result, m;
    int B[10];

	MPI_Init(&argv, &argc);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0){
		printf("Enter M: ");
		scanf("%d", &m);
		numbers = (int *)calloc(size * m, sizeof(int));
		printf("Enter %d number(s): ", size * m);
		for (int i = 0; i < size * m; i++)
			scanf("%d", &numbers[i]);
	}

	MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

	array = (int *)calloc(m, sizeof(int));

	MPI_Scatter(numbers, m, MPI_INT, array, m, MPI_INT, 0, MPI_COMM_WORLD);
	
	int sendResult = 0;
	for (int i = 0; i < m; i++)
		sendResult += array[i];

	sendResult /= m;
	
    MPI_Gather(&sendResult, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);
	int final=0;
	if (rank == 0)
    {
        for(int i=0; i<size; i++)
        {
            final+=B[i];
            printf("%d\t", B[i]);
        }

		printf("The average is : %d\n", final / size);
		free(numbers);
	}
	free(array);
	MPI_Finalize();
	return 0;
}



/*int main(int argc, char* argv[])
{
    int rank, size, N, A[50], B[10], c,i;
    int M=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0)
    {
        printf("Enter M: ");
        scanf("%d", &M);
        // for(int i=0; i<M; i++)
        // {
        MPI_Bcast(&M,1, MPI_INT, 0, MPI_COMM_WORLD);
        // }
        N=size;
        
        for(int i=0; i<M*N; i++)
        {
            fprintf(stdout, "Enter A[%d] value: \n",i);
            fflush(stdout);
            scanf("%d", &A[i]);
        } 

        // for(int i=0; i<M*N; i++)
        // {
        //         MPI_Scatter(A, 1, MPI_INT,&c, 1, MPI_INT, 0, MPI_COMM_WORLD);
        //         if()

        // }
        // for(i=0; i<M*N; i++)
        //      MPI_Scatter(A, M, MPI_INT,&c, M, MPI_INT, 0, MPI_COMM_WORLD);
        int i=0;
        while(i<M*N)
        {
            c=A[i];
            MPI_Scatter(A, 1, MPI_INT,&c, 1, MPI_INT, 0, MPI_COMM_WORLD);
            i++;
        }

                

        
        
        // for(int i=0; i<N; i++)
        //     MPI_Scatter(A, 1, MPI_INT,&c, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }

    fprintf(stdout, "I have received %d in process %d\n", c,rank);
      
    int sum=0;
    for(int i=0; i<M; i++)
        sum+=c;
    printf("SUM FOR %d is %d\n",rank, sum);
    int avg=sum/M;
    MPI_Gather(&sum, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // if(rank==0)
    // {
    //     fprintf(stdout, "The result gathered in the root\n");
    //     fflush(stdout);
    //     for(i=0; i<N; i++)
    //         fprintf(stdout,"%d \t", B[i]);
    //     fflush(stdout);
    // }


    MPI_Finalize();
    return 0;
}*/

/*
int main(int argc, char* argv[])
{
    int rank, size, N, A[10], B[10], c,i;
    MPI_Init(&argc,&argv);
    int M;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0)
    {
        printf("Enter M: ");
        scanf("%d", &M);
        // for(int i=0; i<M; i++)
        // {
        MPI_Bcast(&M,1, MPI_INT, 0, MPI_COMM_WORLD);
        // }
        N=size;
        
        for(int i=0; i<M*N; i++)
        {
            fprintf(stdout, "Enter A[%d] value: \n",i);
            fflush(stdout);
            scanf("%d", &A[i]);
        } 

        int i=0;
        while(i<M*N)
        {
            c=A[i];
            MPI_Scatter(A, 1, MPI_INT,&c, 1, MPI_INT, 0, MPI_COMM_WORLD);
            i++;
        }

    }

    MPI_Scatter(A, 1, MPI_INT,&c, 1, MPI_INT, 0, MPI_COMM_WORLD);
    fprintf(stdout, "I have received %d in procesws %d\n", c,rank);
    fflush(stdout);
    // c=c*c;
    MPI_Gather(&c, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // if(rank==0)
    // {
    //     fprintf(stdout, "The result gathered in the root\n");
    //     fflush(stdout);
    //     for(i=0; i<N; i++)
    //         fprintf(stdout,"%d \t", B[i]);
    //     fflush(stdout);
    // }
    MPI_Finalize();
    return 0;
}*/
//ERROR:
// I have received 1 in procesws 0
// I have received 2 in procesws 1
// I have received 3 in procesws 2
// I have received 4 in procesws 3
// *** stack smashing detected ***: terminated

// q2.out:7434 terminated with signal 6 at PC=7fcb57e969fc SP=7ffff69f7a50.  Backtrace:

// q2.out:7434 terminated with signal 11 at PC=7fcb575f783e SP=7ffff69f6a10.  Backtrace:

// ===================================================================================
// =   BAD TERMINATION OF ONE OF YOUR APPLICATION PROCESSES
// =   PID 7434 RUNNING AT lpcp-09
// =   EXIT CODE: 139
// =   CLEANING UP REMAINING PROCESSES
// =   YOU CAN IGNORE THE BELOW CLEANUP MESSAGES
// ===================================================================================
// YOUR APPLICATION TERMINATED WITH THE EXIT STRING: Segmentation fault (signal 11)
// This typically refers to a problem with your application.
// Please see the FAQ page for debugging suggestions
