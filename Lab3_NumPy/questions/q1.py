# Write a program to find the factors of a given number (get input from user) using for loop.

import numpy as np
import pandas as pd
from icecream import ic

n=int(input("Enter number: "))
print("The factors are: \n")
for i in range(1,n+1):
	if (n%i==0):
		# ic(i)
		print(i)