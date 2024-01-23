#Write a python program to implement simple calculator which perform addition, 
#subtraction, multiplication, and division

import re
 
test_str = input("Enter input string: ")
print("The original string is : " + test_str)
res = eval( test_str)
print("The evaluated result is : " + str(res)) 