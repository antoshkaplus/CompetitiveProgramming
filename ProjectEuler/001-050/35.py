"""
The number, 197, is called a circular prime because all rotations of the digits: 
197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?
"""

from math import sqrt

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
  
  
bound = 1000000

primes = find_primes(bound)

# exclude that can devided by 2
i = 0
while primes[i] < 10: i+=1
# sorted list of primes
prime_strs = {}
for p_i,p in enumerate(primes[i:]):
  p = str(p)
  flag = True
  for d in p: 
    if int(d)%2 == 0: 
      flag = False
      break      
  if flag: prime_strs[p] = 0    
for p in map(str,primes[:i]):
  prime_strs[p] = 0
  
prime_circular = []      
for k,v in prime_strs.iteritems():
  if v == 0: 
    p_c = [k]
    flag = True
    for i in range(1,len(k)):
      t = k[i:]+k[:i]
      if t in prime_strs:
        if p_c.count(t) == 0:
          p_c.append(t)
          prime_strs[t] = 1
      else:
        flag = False
        break
    
    if flag: prime_circular.extend(p_c)
     
     
for i in sorted(map(int,prime_circular)):
  print i     
print len(prime_circular)    
    
       
        
        
        
        
   
   
   
   
   
   
   
   
   





  