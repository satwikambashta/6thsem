# Create a data frame with column- Name, Quiz_1 /10, In-Sem_1 /15, Quiz_2 /10 and In-Sem_2 /15. Now insert a column
# Total and find the total and mean as given in the below table.

import pandas as pd
from icecream import ic
import numpy as np


df=pd.DataFrame({'Name':['A','B'], 'Quiz1':[9,8], 'Insem1':[14,13], 'Quiz2':[8,10], 'Insem2':[12,14]})
df['Total']=df[['Quiz1','Insem1','Quiz2','Insem2']].sum()
df.loc['mean']=df[['Quiz1','Insem1','Quiz2','Insem2']].mean()
print(df)