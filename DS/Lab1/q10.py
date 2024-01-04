y=[11, -21, 0, 45, 66, -93]
print(y)
for x in y:
    if x%2==0:
        y.remove(x)
print('LIST:', y)
