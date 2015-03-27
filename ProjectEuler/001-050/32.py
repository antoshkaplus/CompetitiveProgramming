"""
We shall say that an n-digit number is pandigital if it makes use of all 
the digits 1 to n exactly once; for example, the 5-digit number, 15234, 
is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 * 186 = 7254, containing multiplicand, 
multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product 
identity can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be 
sure to only include it once in your sum.
"""

n1 = 3
n2 = 2
n3 = 4

k = 5 # how many to choose
n = 9
seq = range(1,n+1)
seq[n-k+1:] = seq[:n-k:-1]

res = []

m = 0

while True:
 
  for n1 in range(1,2+1):
    n2 = 5-n1
    prod = [s for s in str(int("".join(map(str,seq[:n1])))*int("".join(map(str,seq[n1:n1+n2]))))]
    if sorted(prod,reverse=True) == map(str,seq[n1+n2:]):
      print prod,int("".join(map(str,seq[:n1]))),int("".join(map(str,seq[n1:n1+n2])))
      if res.count(prod) == 0: res.append(prod)
  
  m+=1  
  
  i = k-1
 
  while i != -1:
    
    s = seq[i]
    s_i = -1
    for j,el in enumerate(seq[:i:-1]):
      if el > s: 
        s_i = n-j-1
        break

    if s_i != -1:
      seq[i], seq[s_i] = seq[s_i], seq[i]
      if i != k-1:
        d = n-len(seq[i+1:k+1])-1
        seq[i+1:k+1], seq[:d:-1] = seq[:d:-1], seq[i+1:k+1]
        seq[k:] = seq[:k-1:-1]
      break 
       
    i -= 1    
  
  
  if i == -1: break # permutations finished

print res

print m

sum = 0
for r in res:
  print int("".join(r))
  sum += int("".join(r))
print sum
    



    
  