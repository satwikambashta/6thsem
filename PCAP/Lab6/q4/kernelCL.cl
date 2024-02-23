__kernel void str_rev(__global char*A, __constant int* len, __global char*c)
{
    int i= get_global_id(0);
    int pos=*len;
    C[pos-i-1]= A[i];
}