__kernel void vector_bin(__global int *A, __global int *C) {

  int i = get_global_id(0);
  C[i]=~A[i];
//   int bin=0, k=0;
//   int q=A[i];
//   int comp[100];
//   while(q!=0)
//   {
//     comp[i++] = q % 10;
//     if(A[i] == '1')
//     {
//             comp[i] = '0';
//     }
//     else if(A[i] == '0')
//     {
//             comp[i] = '1';
//     }
//     q=q/10;
//     bin++;
//   }
//     for(int i=0; i<bin; i++)
//     {
//         k=k*10+comp[i];
//     }
//   C[i]=k;
  
}
