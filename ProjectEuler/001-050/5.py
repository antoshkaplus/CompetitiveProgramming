"""
2520 is the smallest number that can be divided by each of the numbers 
from 1 to 10 without any remainder.
What is the smallest positive number that is evenly divisible by all 
of the numbers from 1 to 20?
"""

n = 20

a = n*[True]
a[0] = False

result = 1
for i in range(2,n+1):
  if a[i-1]:
    for j in range(i-1+i,n,i):
      a[j] = False
    cur = 1
    while cur*i < n: cur*=i
    result*=cur
    
print result    