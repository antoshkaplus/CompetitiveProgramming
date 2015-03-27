"""
By replacing the 1st digit of *3, it turns out 
that six of the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, 
this 5-digit number is the first example having seven primes among 
the ten generated numbers, yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. 
Consequently 56003, being the first member of this family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number 
(not necessarily adjacent digits) with the same digit, is part of an eight prime value family.
"""


class Patterns:
  def __init__(self,n,k):
    self.seq = (n-k)*[0]+k*[1]
    self.n = n
    self.k = k
    
  def get(self):
    return self.seq
    
  def next(self):
    n = self.n
    seq = self.seq
    
    res = True
    
    i = n-1
    # while can't shift one 
    while i > 0 and not (seq[i]==1 and seq[i-1]==0): i-=1    
    
    # able to shift 
    if i != 0:
      seq[i-1] = 1 
      s = sum(seq[i:])-1
      seq[i:]=len(seq[i:])*[0]        
      seq[n-s:]=s*[1]
    else: res = False
    
    return res
    

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
      
      
def upper_bound_index(seq,b,i_st=0,i_fin=None):
  """ finding index i in sequence such that
      (seq[i] >= b) and (seq[i-1] < b if exists) """
  if i_fin == None: 
    i_fin = len(seq) - (1 if len(seq) else 0)    
     
  found = True
  if seq == [] or seq[i_fin] < b: found = False
  else:
    if seq[i_st] == b: i_fin = i_st
    else:
      while i_fin-i_st > 1:
        i = (i_fin+i_st)//2
        if seq[i] < b:
          i_st = i
        else:
          i_fin = i      
  return i_fin,found




max_symbs = 6
bound = 10**max_symbs
primes = find_primes(bound)


import sys

n = 1 # number of symbols
b_st = 1
b_fin = 10
while b_fin <= bound:
  # forming primes of some number of symbols
  i_st,f_st = upper_bound_index(primes,b_st)
  i_fin,f_fin = lower_bound_index(primes,b_fin-1)
  
  # if founded required bounds
  if f_st and f_fin:
    seq = map(str,primes[i_st:i_fin])
    for i in range(1,n):
      pat_obj = Patterns(n,i)
      while True:
        spec_list = []
        
        pat = pat_obj.get()
        pat_dict = {}
        for s in seq:
          key_seq = "".join([w for i,w in enumerate(s) if pat[i]])
          
          rest_seq = "".join([w for i,w in enumerate(s) if not pat[i]])
          repeat = True
          r_samp = rest_seq[0]
          for r in rest_seq:
            if r != r_samp: 
              repeat = False
              break
          if repeat:
            if key_seq in pat_dict: pat_dict[key_seq].append(s)
            else: pat_dict[key_seq] = [s]
          
        for value in pat_dict.values():          
          if len(value)==8:
            spec_list.append(value)
          
        if spec_list != []:
          for s in spec_list:
            print min(s),s
          sys.exit(0) 
        
        if not pat_obj.next(): break
  
  n+=1
  b_st = b_fin
  b_fin *= 10
  
  
  
