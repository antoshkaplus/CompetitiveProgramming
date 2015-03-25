
from primes import find_primes
from math import sqrt

n = 10**6

p_arr = [set() for i in range(n)]

b_arr = n*[False]
b_arr[0] = True
for i,b in enumerate(b_arr):
  if not b:
    for j in range(i,n,i+1):
      p_arr[j].add(i+1)
      b_arr[j] = True

      
s = 0
for i,p in enumerate(p_arr):
  if i==0: continue
  m = i+1
  u = 1
  for c in p:  
    m /= c
    u *= c-1
  u *= m
  s += u
  
print s  