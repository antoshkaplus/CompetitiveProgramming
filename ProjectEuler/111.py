"""
Considering 4-digit primes containing repeated digits 
it is clear that they cannot all be the same: 1111 
is divisible by 11, 2222 is divisible by 22, and so on. 
But there are nine 4-digit primes containing three ones:
  1117, 1151, 1171, 1181, 1511, 1811, 2111, 4111, 8111

We shall say that M(n,d) represents the maximum number 
of repeated digits for an n-digit prime where d is the 
repeated digit, N(n,d) represents the number of such primes, 
and S(n, d) represents the sum of these primes.

So M(4,1) = 3 is the maximum number of repeated digits 
for a 4-digit prime where one is the repeated digit, 
there are N(4, 1) = 9 such primes, and the sum of these 
primes is S(4, 1) = 22275. It turns out that for d = 0, 
it is only possible to have M(4, 0) = 2 repeated digits, 
but there are N(4, 0) = 13 such cases.

In the same way we obtain the following results for 4-digit primes.

For d = 0 to 9, the sum of all S(4, d) is 273700.
Find the sum of all S(10, d).
"""

import math 
import string


def find_primes(bound) :
  primes = [True]*bound
  primes[0] = False
  
  result = []
  for i in range(1,bound+1) :
    if primes[i-1]:
      result.append(i)
      primes[2*i-1:bound:i] = [False]*len(primes[2*i-1:bound:i])
  return result

  
n_min = 10**9
n_max = 10**10-1
div_primes = find_primes(int(math.sqrt(n_max)))
primes = []

n = n_min
while n <= n_max:
  is_prime = True
  for div in div_primes:
    if n%div == 0:
      is_prime = False
      break
  if is_prime: primes.append(n)
  
str_primes = map(str,primes)  
    
    
big_sum = 0    
for d in string.digits:
  # finding maximum repeats of digit in primes
  max_rep = 0
  for p in str_primes:
    rep = len(p)-len(string.translate(p,None,d))
    if rep > max_rep: max_rep = rep
  # summing primes that have same number of repeats        
  for i,p in enumerate(str_primes):
    if len(p)-len(string.translate(p,None,d)) == max_rep:
      big_sum += primes[i]
      
print big_sum
      


