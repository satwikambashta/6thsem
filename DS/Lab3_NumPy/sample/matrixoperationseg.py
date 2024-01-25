import numpy as np

A = np.array( [[1,1],[0,1]] )
B = np.array( [[2,0],[3,4]] )
print(A*B)
# elementwise product
np.array([[2, 0],
[0, 4]])
A.dot(B)
# matrix product
np.array([[5, 4],
[3, 4]])
# (OR)
np.dot(A, B)
np.array([[5, 4],
[3, 4]])
# another matrix product
b = np.arange(12).reshape(3,4)
print(b)
np.array([[ 0, 1, 2, 3],
[ 4, 5, 6, 7],
[ 8, 9, 10, 11]])
b.sum(axis=0)
np.array([12, 15, 18, 21])# sum of each column
b.sum(axis=1)
np.array([6, 22, 38])