__kernel void vector_ones_complement(__global char * A, __global char * B) {
    int i = get_global_id(0);
    int m = 4;
    int k = i * m;
    for (int j = 0; j < m; j++)
    {
             if(A[k+j]==0)
                  B[k+j]=1;
              else if(A[k+j]==1)
                  B[k+j]=0;
    }
}
