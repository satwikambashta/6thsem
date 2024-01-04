x=int(input(' Enter num: '))
y=int(input(' Enter num: '))
z=int(input(' Enter num: '))

if x>=y:
    if(x>=z):
        print(x, 'is the largest')
    else:
        print(z, 'is the largest')
elif y>=x:
    if(y>=z):
        print(y, 'is the largest')
    else:
        print(z, 'is the largest')
else:
    print(z,'is the largest')

