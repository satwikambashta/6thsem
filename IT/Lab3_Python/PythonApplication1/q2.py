# Write a python program to reverse a content a file and store it in another file.

with open("myfile1.txt") as f:
	data=f.read()

new_data=data[::-1]
print(new_data)
f.close()

#print(new_data)
#i=(data)
#print(i)

with open("myfile.txt", "w+") as file:
	file.write(new_data)