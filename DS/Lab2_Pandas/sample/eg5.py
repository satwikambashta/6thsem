import pandas as pd
import numpy as np

dates=pd.date_range('20130101', periods=100)
df = pd.DataFrame(np.random.randn(100,4), index=dates, columns=list('ABCD'))
# print(df.head()) #To view first 5 records
# print(df.tail()) #To view last 5 records
# print(df.index) #To view the index
# print(df.columns) #To view the column names
# print(df.T) #To transpose the df
# print(df.sort_index(axis=1, ascending=False)) #Sorting by Axis
# print(df.sort_values(by='B')) #Sorting by Values
# print(df[0:3]) #Slicing the rows
# print(df['20130105':'20130110']) #Slicing with index name
# print(df.iloc[0]) #slicing with row and column index (like 2D Matrix)
# print(df.iloc[0,:2]) #will fetch 1st row, first 2 columns
# print(df.iloc[0,0]) #will fetch 1st row, 1st column element (single element)
# print(df['A'])#which yields a Series
# print(df['A','B']) #Selecting more than one column
# print(df[['A','B']][:5]) #Selecting more than one column, with selected number of records

#BOOLEAN INDEXING
df[df.A>0]
df[‘F’]=[‘Male’,’Female’,’Female’,’Male’,’Female’,’Female’]