# Operations on Arrays (use numpy wherever required):
# a) Create array from list with type float
# b) Create array from tuple
# c) Creating a 3X4 array with all zeros
# d) Create a sequence of integers from 0 to 20 with steps of 5
# e) Reshape 3X4 array to 2X2X3 array
# f) Find maximum and minimum element of array, Row wise max and min, column wise max
# and min and sum of elements. (Use functions max(), min(), sum())

import numpy as np
import pandas as pd
from icecream import ic
#a
list1=[1,2,3,4]
arr1=np.array(list1, dtype="float")
print(arr1)
#b
tuple1=(7,6,5,4)
arr2=np.array(tuple1, dtype="float")
print(arr2)
#c
print("Zeroes matrix:")
zeroes1=np.zeros((3,4))
print(zeroes1)
#d
print(np.arange(0,20,5))

#e
e=zeroes1.reshape(2,2,3)
print(e)

#f

f=np.array([[1,11,2],[3,55,6]])
print("The array: ")
print(f)
print(f.max(axis=0))
print(f.min(axis=0))
print(f.max(axis=1))
print(f.min(axis=1))