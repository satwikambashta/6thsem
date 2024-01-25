import numpy as np

a = np.arange(15).reshape(3, 5)
np.array([[ 0, 1, 2, 3, 4],
[ 5, 6, 7, 8, 9],
[10, 11, 12, 13, 14]])
#to check the dimension
print(a.shape)
print(a.size) # will return total elements in matrix (here 15)
# to transpose a matrix
print(a.T) # transposed to 5x3 matrix