"""
In England the currency is made up of pound, and pence, p, 
and there are eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, pound 1 (100p) and pounds 2 (200p).
It is possible to make pounds 2 in the following way:

1pound1 + 150p + 220p + 15p + 12p + 31p
How many different ways can pounds 2 be made using any number of coins?
"""

n = 200

t = (n+1)*[0]
t[0] = 1
for i in [1,2,5,10,20,50,100,200]:
  t = [sum([t[j-k*i] for k in range(0,int(j/i)+1)]) for j in range(0,n+1)]

print t[n]

# not my in the bottom

vals = [1]+[0]*200
for coin in [1,2,5,10,20,50,100,200]:
	for i in range(coin,201):
		vals[i] += vals[i-coin]
print "#31",vals[200]

