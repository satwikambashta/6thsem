#Write a python program to implement simple calculator which perform addition, 
#subtraction, multiplication, and division

def main():
	a=int(input("Enter number 1:"))
	b=int(input("ENter number 2: "))
	c=input("ENter operator: ")

	if(c=="/"):
		print(a/b)
	elif(c=="*"):
		print(a*b)
	elif(c=="+"):
		print(a+b)
	elif(c=="-"):
		print(a-b)
	else:
		print("Unsupported operator")
		
if __name__ == '__main__':
	main()