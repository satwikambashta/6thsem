import pandas as pd
import matplotlib.pyplot as plt
# %matplotlib inline

df=pd.read_csv('././lab2_req_files/xyz.csv',header=None)
print(df.head())
print(df.tail())
#attach header
df.columns=['preg','glu','bp','sft','ins','bmi','dpf','age','class']

#Let us visualize the scatter plot of two continuous variable

plt.scatter(df['bmi'],df['glu'])
plt.xlabel('bmi')
plt.ylabel('Glucose')
plt.title('bmi vs glucose')
plt.show()

#Let us visualize the histogram of another continuous variable ‘Age’
plt.hist(df['age'])
plt.show()

#box plot
plt.boxplot(df['age'])
plt.show()

#W = pd.read_csv('xyz.xls',header=None)
#W.head() #XLS file format also, we can read using pd.read_csv
#D= np.loadtxt(‘xyz.data',delimiter=",")
#D[:5,:] # this file is loaded in Numpy 2D array format
# Reading a XLSX file format
#G=pd.read_excel(xyz.xlsx',sheet_name='Sheet1')
#Pandas can read table tabs off of html. For example:
#B = pd.read_html('http://www.fdic.gov/bank/individual/failed/banklist.html')
# Reading a TXT file format
#H = pd.read_table('HR.txt')