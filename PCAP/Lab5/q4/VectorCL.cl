__kernel void vector_bin(__global const int* A, __global int* C) {
        int i = get_global_id(0);
        int bin = A[id];
        int dec =  0;
        for (int j =  0; i <  32; j++) {
            int twop =  1 << j;
            if ((bin & twop) !=  0) {
                dec += twop;
            }
        }
        C[i] = dec;
    
}