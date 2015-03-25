"""
The first two consecutive numbers to have two 
distinct prime factors are:
14 = 2*7
15 = 3*5

The first three consecutive numbers to have three distinct prime factors are:
644 = (2**2)*7*23
645 = 3*5*43
646 = 2*17*19.

Find the first four consecutive integers to have four distinct primes factors. 
What is the first of these numbers?
"""
b = 10**6
d = 4

table = b*[0]
table[0] = 1
for i,t in enumerate(table):
  if not t:
    table[i:b:i+1]=map(lambda x:x+1,table[i:b:i+1])

 
for i in range(b):
  if all(map(lambda x:x==d,table[i:i+d])):
    print i+1
    break
  




