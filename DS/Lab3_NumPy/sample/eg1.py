import numpy as np
A = np.array ([2,5,10])
print(A.dtype)
B=np.array ([2.4,10.6,5.2])
print(B.dtype)

A=np.array([(3,4,5),(12,6,1)])
print(A)

Z=np.zeros((2,4)) # will create zero matrix of dimension 2x4
print(Z)

S=np.arange(10,30,5)
print(S) #will give (10,15,20,25,30), with step size of 5

np.arange( 0, 2, 0.3 ) # it accepts float arguments
print(np.array([ 0. , 0.3, 0.6, 0.9, 1.2, 1.5, 1.8]))