"""
The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, 
is unusual in two ways: 
(i) each of the three terms are prime, and, 
(ii) each of the 4-digit numbers are permutations of one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, 
exhibiting this property, but there is one other 4-digit increasing sequence.

What 12-digit number do you form by concatenating the three terms in this sequence?
"""

"""
create set of primes
create lists of three by choosing elems which make up inc on 3330 seq
leave that, which consists of permutations of each other
"""

# identify number by digit content
def dig_ident(x):
  p = 10*[0]
  while x != 0:
    x,d = divmod(x,10)
    p[d]+=1
  return "".join(map(str,p))
  
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

# choosing primes only with 4 digits 
primes = find_primes(10**4)
i = 0
while primes[i] <= 1000: i+=1
primes = primes[i:]  

for p in primes:
  if (p+3330 in primes) and (p+6660 in primes): print p

"""
# 
data = {}
for p in primes:
  di = dig_ident(p)
  if di not in data: data[di] = []
  data[di].append(p)

for v in data.values():
  if len(v) >= 3:
    for i,p in enumerate(v[:-1]):
      for pp in v[i+1:]:    
        if abs(p-pp)==3330: print p,pp,v
"""    
    
    
  
  
  
  
  