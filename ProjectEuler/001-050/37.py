"""
The number 3797 has an interesting property. Being prime itself, 
it is possible to continuously remove digits from left to right, 
and remain prime at each stage: 3797, 797, 97, and 7. 
Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable 
from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
"""


from math import sqrt
from sets import Set

# returns list of primes in segment [1:n]
def find_primes(n):
  primes = []
  table = n*[True]
  table[0] = False
  for i, el in enumerate(table):
    if el: 
      primes.append(i+1)  
      table[2*i+1:n:i+1] = len(table[2*i+1:n:i+1])*[False]
  return primes
  
primes_tr = ["23","53"]

rank = 7
b = 10**rank

dig_list = ["1","3","7","9"]
dig_set = Set(dig_list)

primes = Set()
for p in find_primes(b):
  flag = True
  for i in str(p):
    if i not in dig_set:
      flag = False
      break
  if flag: primes.add(str(p))
 

Q = ["3","7"]
while Q != [] and len(Q[0]) <= rank:
  q = Q
  Q = []
  for p in q:
    
    # 3
    p1 = "".join(p+"3")
    if p1 in primes:
      flag = True    
      for i in range(1,len(p1)-1):
        if p1[i:] not in primes:
          flag = False
          break
      if flag: primes_tr.append(p1)
      
      Q.append(p1)
    
    # 7  
    p2 = "".join(p+"7")
    if (p2.count("7") != 3) and (p2 in primes):
      flag = True    
      for i in range(1,len(p1)-1):
        if p2[i:] not in primes:
          flag = False
          break
      if flag: primes_tr.append(p2)    
      
      Q.append(p2)
    
    # 9
    p3 = "".join(p+"9")
    if p3 in primes: Q.append(p3)
    
    # 1
    p4 = "".join(p+"1")
    if p4 in primes: Q.append(p4)


for p in primes_tr:
  print p

print sum(map(int,primes_tr))











