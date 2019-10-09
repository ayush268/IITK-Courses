from random import randint
import numpy as np
v = randint(5,10)
e = randint(2*v,3*v)

d = np.zeros((v+1,v+1))

print(str(v)+" "+str(e))
count = 0

while count<e:
	a = randint(1,v)
	b = randint(1,v)
	if(a==b):
		continue
	elif d[a][b]!=0:
		continue
	else:
		count = count+1
		d[a][b] = 1
		d[b][a] = 1
		print(str(a)+" "+str(b))

