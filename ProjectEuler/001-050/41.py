"""
We shall say that an n-digit number is pandigital if it makes use 
of all the digits 1 to n exactly once. 
For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists?
"""

bound = 7654321

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

primes = find_primes(bound)
for j in primes[::-1]:
  pr_len = len(str(j))
  pat_dream = [0]+pr_len*[1]+(7-pr_len)*[0]+[0,0]
  pat = 10*[0]
  d = j
  while d != 0:
    d,r = divmod(d,10)
    pat[r]+=1
  if pat == pat_dream:
    print j  
    






