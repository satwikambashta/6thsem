__kernel void vector_swap(__global int* A, __global int* LIST_SIZE, __global int* C) {
    int i = get_global_id(0);

    if (i >= LIST_SIZE) {
        return;
    }

    // Only swap if the current element is not the last one
    if (i %  2 ==  0 && i +  1 < LIST_SIZE) {
        int temp = A[i];
        C[i] = A[i +  1];
        C[i +  1] = temp;
    } else {
        // Copy the element as is if it's not adjacent to another element
        C[i] = A[i];
    }
}
