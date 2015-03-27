
from primes import find_primes
from math import sqrt

def perms(n1,n2):
  n1 = map(int,str(n1))
  n2 = map(int,str(n2))
  d1 = {}
  for c in n1:
    if c in d1: d1[c] += 1
    else: d1[c] = 1
  d2 = {}
  for c in n2: 
    if c in d2: d2[c] += 1
    else: d2[c] = 1
  return d1 == d2

  
n = 10**7


bound = 5000
q = 1./3
p = find_primes(bound)
p = p[int(len(p)*q):]

res = []

for i,r1 in enumerate(p):
  for r2 in p[i+1:]:
    if r1*r2 < n and perms((r1-1)*(r2-1),r1*r2):
      res.append((r1,r2))
      
r = max(res,key=lambda x: 1.*(x[0]-1)*(x[1]-1)/(x[0]*x[1]))
print r[0]*r[1]












