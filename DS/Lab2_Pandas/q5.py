# a) Create two data frames df1 and df2. df1 contains one column ‘Name’ and df2 contains 4 columns ‘Maths’,
# ‘Physics’, ‘Chemistry’ and ‘Biology’ .
# b) Concatenate two data frames df1 and df2. Now insert one column ‘Total’ to the new data frame df_new
# and find the sum of all marks.

import pandas as pd
from icecream import ic
import numpy as np

df1=pd.DataFrame({'Name':['A', 'B']})
df2=pd.DataFrame({'Maths':[18,20], 'Physics':[20,19], 'Chemistry':[18,19], 'Biology':[19,20]})
# print(df1)
# print(df2)
dfNew=pd.concat([df1,df2],axis=1)
print(dfNew)
dfNew['Total']=df2['Maths']+df2['Physics']+df2['Chemistry']+df2['Biology']

print(dfNew)