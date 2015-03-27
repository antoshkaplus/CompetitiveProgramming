"""
The prime factors of 13195 are 5, 7, 13 and 29.
What is the largest prime factor of the number 600.851.475.143?
"""

from math import sqrt

        
          
number = 600851475143
n = int(sqrt(number))
s = (n-1)*[True]
for i in range(2,n+1):
  if s[i-2]: s[i+i-2:n-1:i] = len(s[i+i-2:n-1:i])*[False]
  
  
for i in range(n,1,-1):
  if s[i-2] and not (number%i):
    print i
    break
    