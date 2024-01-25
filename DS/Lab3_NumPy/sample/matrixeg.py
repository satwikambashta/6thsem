import numpy as np
b=np.array([[ 0, 1, 2, 3],
[10, 11, 12, 13],
[20, 21, 22, 23],
[30, 31, 32, 33],
[40, 41, 42, 43]])
b[2,3] #will fetch 23
b[0:5,1] #or b[:5,1] or b[:,1] #will fetch [1,11,21,31,41]
b[-1,:] # will fetch last row
b[:,-1] # will fetch last col
for row in b:
	print (row) # will print every rowfor element in b.flat:
# print (element) # will show all elements of b in 1−D array
# Changing the shape of a matrix
b.ravel() # returns the array flattened to (1x 20)
# Later, we can convert 5