"""
A palindromic number reads the same both ways. 
The largest palindrome made from the product of two 2-digit numbers is 9009 = 91  99.
Find the largest palindrome made from the product of two 3-digit numbers.
"""
n_max = 999
n_min = 100

max_pal = 0
for i in range(n_max,n_min-1,-1):
  out = False
  for j in range(n_max,i-1,-1):
    k = str(i*j)
    if k[:] == k[::-1]:
      if max_pal < int(k):
        max_pal = int(k)      
    
print max_pal
  