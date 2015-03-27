
from math import sqrt
from primes import find_primes

n = 10**6
p = find_primes(int(sqrt(n)))

s = 1
for q in p:
  if s*q > n: break
  s *= q
  
print q,s
    