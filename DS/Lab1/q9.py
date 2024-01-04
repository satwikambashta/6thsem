y=[11, -21, 0, 45, 66, -93]

pos,neg=0,0

for x in y:
    if x<0:
        neg+=1
    else:
        pos+=1
print('Positive numbers: ', pos, 'Negative numbers: ', neg)