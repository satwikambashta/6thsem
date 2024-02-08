__kernel void vector_bin(__global char * A, __global char * C) {
    int i = get_global_id(0);
    int m = 4;
    int k = i * m;
    for (int j = 0; j < m; j++)
    {
             if(A[k+j]==0)
                  C[k+j]=1;
              else if(A[k+j]==1)
                  C[k+j]=0;
    }
}
