"""
The fraction 49/98 is a curious fraction, as an inexperienced mathematician 
in attempting to simplify it may incorrectly believe that 49/98 = 4/8, 
which is correct, is obtained by cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, 
less than one in value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
"""

# stupid problem


def euclid(a,b):
  res = None
  if a == b: res = a
  else:
    if a>b : a-=b
    else: b-=a
    res = euclid(a,b)
  return res   
  
min, max = 10, 99

for i in range(1,9+1):
  for j in range(1,i):
    for k in range(1,9+1):
      n = i+10*j
      d = 10*i+k
      if n >= d: break
      
      p = euclid(n,d)
      
      j_n = n/p
      k_d = d/p
      
      if j*k_d == k*j_n:
        print n,d      
     
  for j in range(i,9+1):
    for k in range(1,9+1):
      d = i+10*j
      n = 10*i+k
      if n >= d: break
      
      p = euclid(n,d)
      
      j_d = d/p
      k_n = n/p
      
      if j*k_n == k*j_d:
        print n,d          
      
      
