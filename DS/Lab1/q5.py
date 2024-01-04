list = [ 'MIT', 12345 , 3.14, 'TTT', 69.2, 'MIT', 'CAT', 2323]
tinylist = [123, 'BALL']
print (list) # Prints complete list
print (list[0]) # Prints first element of the list
print (list[1:3]) # Prints elements starting from 2nd till 3rd
print (list[2:]) # Prints elements starting from 3rd element
print (tinylist * 2) # Prints list two times
print (list + tinylist) # Prints concatenated list
list.append('maths')
print(list)
del list[2]
print(len(list))
print('Number of times MIT occurs:' ,list.count('MIT'))
list.insert (2, 'maths')
print(list)