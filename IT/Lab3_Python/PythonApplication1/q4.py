#Write a python program to sort words in alphabetical order.

def main():
	string1=input("Enter a word: ")
	i=len(string1)
	#for x in range(i):
	#	if(string1[x]<65):
	#		print("Invalid")
	print(str(sorted(string1)))
if __name__ == '__main__':
	main()