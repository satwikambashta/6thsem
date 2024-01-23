print("yahoo!") if 3 > 2 else 2

li = []
li.append(1)
li.append(2)
li.append(4)
print(li)

li.pop()
print(li)

print(li[1:3])
other_li = [4, 5, 6]
print(len(li))
print(li.extend(other_li))

empty_dict = {}
filled_dict = {"one": 1, "two": 2, "three": 3}
 
print(filled_dict["one"])
print(list(filled_dict.keys()))
del filled_dict["one"] 
some_set = {1, 1, 2, 2, 3, 4}
print(some_set)
some_set.add(5) 
print(some_set)


some_var = 5
if some_var > 10:
 print("some_var is totally bigger than 10.")
elif some_var < 10: # This elif clause is optional.
 print("some_var is smaller than 10.")
else: # This is optional too.
 print("some_var is indeed 10.")


animals = ["dog", "cat", "mouse"]
for i, value in enumerate(animals):
 print(i, value)


#  contents = {"aa": 12, "bb": 21}
# with open("myfile1.txt", "w+") as file:
#  file.write(str(contents)) # writes a string to a file
# with open("myfile2.txt", "w+") as file:
#  file.write(json.dumps(contents)) # writes an object to a file
# # Reading from a file
# with open('myfile1.txt', "r+") as file:
#  contents = file.read() # reads a string from a file
# print(contents)
# # print: {"aa": 12, "bb": 21}
# with open('myfile2.txt', "r+") as file:
#     contents = json.load(file) 
 
def all_the_args(*args, **kwargs):
 print(args)
 print(kwargs)
all_the_args(1, 2, a=3, b=4) 

# def main():
#  # sys.argv contains command line arguments.
#  # This assigns a list of all but the first arg into a local 'args' var.
#  args = sys.argv[1:]
 
#  # important syntax -- loop of variable 'filename' over the args list.
#  for filename in args:
#  # detect scary filenames: if/else and/or/not
#     if filename == 'voldemort' or filename == 'vader':
#         print 'this file is very worrying'
#         cat(filemane, 123, bad_variable)
#     # important point: errors in above line only caught if it is run
#     else:
#     # regular case
#         cat(filename)
# print( 'all done' )

# if __name__ == '__main__':
#  main()