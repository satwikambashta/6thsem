import pandas as pd
import math

df=pd.read_excel('/home/CSE210905272/DistributedSystems/Lab5_MapReduce/Lab5_Required_Files/German_Credit.xlsx', engine='openpyxl')
plt.scatter(df['CreditAmount'], df['DurationOfCreditInMonths'])
print(plt.show())