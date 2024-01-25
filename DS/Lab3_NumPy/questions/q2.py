# Find the sum of columns and rows using axis.

import numpy as np
from icecream import ic

a=np.array([[ 0, 1, 2, 3, 4],
[ 5, 6, 7, 8, 9],
[10, 11, 12, 13, 14]])
ic("ROW sum:")
print(a.sum(axis=1))
ic("COLUMN sum:")
print(a.sum(axis=0))