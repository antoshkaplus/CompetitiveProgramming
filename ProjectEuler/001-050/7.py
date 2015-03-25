"""
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13,
we can see that the 6th prime is 13.

What is the 10 001st prime number?
"""

from math import log
from math import sqrt

# if n not less than 6
def upper_bound_on_the_nth_prime(n):
  result = n*log(n) + n*log(log(n)) 
  if n > 7022:
    result -= n*0.9385
  return result

def find_the_nth_prime(k):   
  n = int(upper_bound_on_the_nth_prime(k))
  j = 0
  s = (n-1)*[True]
  for i in range(2,n+1):
    if s[i-2]: 
      j+=1; 
      if j == k: return i
      s[i+i-2:n-1:i] = len(s[i+i-2:n-1:i])*[False]
         
print find_the_nth_prime(10001)    