# Define a dictionary containing Students data {Name, Height, Qualification}.
# a) Convert the dictionary into DataFrame
# b) Declare a list that is to be converted into a new column (Address}
# c) Using 'Address' as the column name and equate it to the list and display the result.

import pandas as pd
from icecream import ic
import numpy as np
dict1={'Name':['A','B','C'], 'Height':[180,183,190], 'Qualification':'UG'}
studentData= pd.DataFrame(dict1)
print(studentData)

list1=['Shivaji Peth', 'Budhwar Peth', 'Mangalwar Peth']
studentData['Address']=list1
print(studentData)