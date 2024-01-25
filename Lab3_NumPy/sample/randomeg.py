import random
print(random.choice([1,2,3,4,5]))#, this will pick one number from the list randomly
print(random.choice('python'))#, will pick one character from the string randomly
print(random.randrange(25,50))# will pick one integer between 25 to 50
print(random.randrange(25,50,2))#, will pick one integer between 25 to 50 with step size of 2
print(random.random())#, will pick a random number between 0 to 1
print(random.uniform(5,10))#, will pick a floating point number between 5 to 10
print(random.shuffle([1,2,3,4,5]))#, will shuffle the list elements
print(random.seed(10))#, to get same random value during every execution