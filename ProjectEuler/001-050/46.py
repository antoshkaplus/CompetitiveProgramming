"""
It was proposed by Christian Goldbach that every odd composite number can be 
written as the sum of a prime and twice a square.

9 = 7 + 2*1^2
15 = 7 + 2*2^2
21 = 3 + 2*3^2
25 = 7 + 2*3^2
27 = 19 + 2*2^2
33 = 31 + 2*1^2

It turns out that the conjecture was false.
What is the smallest odd composite that cannot be written as the 
sum of a prime and twice a square?
"""


import sets
import math

b = 10**5

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
  
  
prime_list = find_primes(b)
prime_set = sets.Set(prime_list)

res = None
min = 9
for odd in range(min,b,2):
  if odd not in prime_set:
    flag = False
    for p in prime_list:
      if p < odd:
        r = odd-p
        if math.sqrt(r/2)%1==0:
          flag = True
          break
    if not flag:
      res = odd
      break
      
print res



  
  
  
  
  
  