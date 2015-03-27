"""
The prime 41, can be written as the sum of six consecutive primes:
41 = 2 + 3 + 5 + 7 + 11 + 13

This is the longest sum of consecutive primes that adds 
to a prime below one-hundred.

The longest sum of consecutive primes below one-thousand 
that adds to a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum 
of the most consecutive primes?

"""

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

bound = 10**6

primes = find_primes(bound)

import sets
prime_set = sets.Set(primes)
  
max_len = 0
max_sum = 0

bound_st = int(bound/3)+1
i_st = len(primes)-1
while primes[i_st] > bound_st: i_st-=1
# in reverse order
primes = primes[i_st::-1]

for i,p_st in enumerate(primes):
  p_len = 1
  p_sum = p_st
  for p in primes[i+1:]:
    p_sum+=p
    p_len+=1
    if p_sum > bound: break
    if (p_sum in prime_set) and p_len > max_len: 
      max_len, max_sum = p_len, p_sum
    
    
print max_len,max_sum



  
  
  
  

























