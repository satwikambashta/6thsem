# Define a dictionary containing Students data {Name, Height, Qualification}.
# a) Convert the dictionary into DataFrame
# b) Use DataFrame.insert() to add a column and display the result.

import pandas as pd
from icecream import ic
import numpy as np
dict1={'Name':['A','B','C'], 'Height':[180,183,190], 'Qualification':'UG'}
studentData= pd.DataFrame(dict1)

studentData.insert(1,"Address",['Shivaji Peth', 'Budhwar Peth', 'Mangalwar Peth'])
print(studentData)