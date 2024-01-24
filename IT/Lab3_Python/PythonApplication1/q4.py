#Write a python program to sort words in alphabetical order.

def main():
	string1 = input("Enter a word: ")
	sorted_string = ''.join(sorted(string1))
	print(sorted_string)
if __name__ == '__main__':
	main()
