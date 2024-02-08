import pandas as pd

df = pd.read_excel('/home/CSE210905272/DistributedSystems/Lab5_MapReduce/Lab5_Required_Files/German_Credit.xlsx', engine='openpyxl')
for country in df['CreditAmount']:
    print('%d\t%d' %(country,1))