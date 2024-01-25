# Write a program to transpose a given matrix.

import numpy as np
import pandas as pd
from icecream import ic

A=np.array([[1,2,3],[4,5,6],[7,8,9],[11,12,13]])

print(A)

print(A.shape)
#transpose
A=A.T
print(A)
print(A.shape)