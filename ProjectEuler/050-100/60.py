"""
The primes 3, 7, 109, and 673, are quite remarkable. 
By taking any two primes and concatenating them in any order the result will always be prime. 
For example, taking 7 and 109, both 7109 and 1097 are prime. The sum of these four primes, 792, 
represents the lowest sum for a set of four primes with this property.

Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.
"""

import sets


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


def prime_conc(p1,p2,prime_set):
  res = False
  if (p1+p2 in prime_set) and (p2+p1 in prime_set): res = True
  return res

  
b = 10**8
# all primes are strings !!!!!
prime_list = map(str,find_primes(b))
prime_set = sets.Set(prime_list)

res = None

# {1:[[..],[..]],2:[[..],[..]],5:[[]]
prime_conc_dict = {1:[],2:[],3:[],4:[],5:[]}

k_pr = 5
for p in prime_list:
  prime_conc_dict[1].append([p])
  for length in range(1,k_pr):
    for seq in prime_conc_dict[length]:
      flag = True
      for el in seq: 
        if not prime_conc(el,p,prime_set): 
          flag = False
          break
      if flag: prime_conc_dict[length+1].append(seq+[p]) 
  if prime_conc_dict[k_pr] != []: break

 
print prime_conc_dict[k_pr]
    








  