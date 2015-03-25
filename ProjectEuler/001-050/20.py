"""
n! means nx(n-1)x...x3x2x1

For example, 10! = 10x9x...x3x2x1 = 3628800,
and the sum of the digits in the number 10! 
is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!
"""

import math 
f = math.factorial

n = 100
s = str(f(n))
sum = 0
for i in s:
  sum += ord(i) - ord('0')
  
print sum

