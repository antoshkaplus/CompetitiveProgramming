"""

Starting with 1 and spiralling anticlockwise in the following way, 
a square spiral with side length 7 is formed.

37 36 35 34 33 32 31
38 17 16 15 14 13 30
39 18  5  4  3 12 29
40 19  6  1  2 11 28
41 20  7  8  9 10 27
42 21 22 23 24 25 26
43 44 45 46 47 48 49

It is interesting to note that the odd squares lie along the bottom right diagonal, 
but what is more interesting is that 8 out of the 13 numbers lying along 
both diagonals are prime; that is, a ratio of 8/13  62%.

If one complete new layer is wrapped around the spiral above, a square spiral 
with side length 9 will be formed. If this process is continued, what is the side length 
of the square spiral for which the ratio of primes along both diagonals first falls below 10%?
"""

import math

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


def lower_bound_index(seq,b,i_st=0,i_fin=None):
  """ finding index i in sequence such that
      (seq[i] <= b) and (seq[i+1] > b if exists) """
  if i_fin == None: 
    i_fin = len(seq) - (1 if len(seq) else 0)
  
  found = True
  # if impossible to perform operation
  if seq == [] or seq[i_st] > b: found = False 
  else:
    # if bound at the end of seq
    if seq[i_fin] == b: i_st = i_fin 
    # else finding the bound
    else:
      while i_fin-i_st > 1:
        i = (i_fin+i_st)//2
        if seq[i] > b:
          i_fin = i
        else:
          i_st = i    
  return i_st,found  
  
def is_prime(n):
  res = False
  for p in range(2,int(math.sqrt(n))):
    if n%p==0: break    
  else: 
    res = True
  return res
    
i = 1
n_pr, n_tot = 3, 5
while n_pr*100./n_tot >= 10:
  i+=1
  pp = [2*i*(2*i+1)+1,4*i*i+1,2*i*(2*i-1)+1]
  for p in pp:
    if is_prime(p): n_pr+=1
  n_tot += 4
  
print 2*i+1


  
  
  