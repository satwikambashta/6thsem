
import numpy as np
a = np.array([4.,2.])
b = np.array([3.,8.])
print(np.column_stack((a,b))) # returns a 2D array
print(np.array([[ 4., 3.],
[ 2., 8.]]))

np.hstack((a,b))
# the result is different
np.array([ 4., 2., 3., 8.])
print(np.hstack((a[0],b[0]))) # the result is the same
np.array([[ 4., 3.],
[ 2., 8.]])