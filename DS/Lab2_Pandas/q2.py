# Write a program to print negative Numbers in a List using while loop.


from icecream import ic 
list1 = [1,2,3,-1,2,-3, -9]
i=0
print("Negative numbers: ")
while i < len(list1):
	if list1[i]<0:
		print(list1[i])
	i+=1