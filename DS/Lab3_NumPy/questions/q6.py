# Write a program to find element wise product between two matrices.

import numpy as np
import pandas as pd
from icecream import ic

X=np.array([[12,7,3],
    [4 ,5,6],
    [7 ,8,9]])
Y=np.array([[5,8,1],
    [6,7,3],
    [4,5,9]])

Z=X*Y
print(Z)

X = [[12,7,3],
    [4 ,5,6],
    [7 ,8,9]]

Y = [[5,8,1],
    [6,7,3],
    [4,5,9]]

Z = [[0,0,0],
         [0,0,0],
         [0,0,0]]

for i in range(len(X)):
   for j in range(len(X[0])):
       Z[i][j] = X[i][j] * Y[i][j]

for r in Z:
   print(r)
