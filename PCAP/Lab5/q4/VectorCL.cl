__kernel void vector_bin(__global const int* binaryInput, __global int* decimalOutput) {
        int id = get_global_id(0);
        int binaryValue = binaryInput[id];
        int decimalValue =  0;
        for (int i =  0; i <  32; i++) {
            int powerOfTwo =  1 << i;
            if ((binaryValue & powerOfTwo) !=  0) {
                decimalValue += powerOfTwo;
            }
        }
        decimalOutput[id] = decimalValue;
    
}