"""
The decimal number, 585 = 1001001001_{2} (binary), 
is palindromic in both bases.

Find the sum of all numbers, less than one million, 
which are palindromic in base 10 and base 2.

(Please note that the palindromic number, 
in either base, may not include leading zeros.)
"""

import sys
sys.stdout = file("36.txt","w")

sum = 0

for i in range(1,1000):
  s = str(i)
  d = len(s)
  p1_10 = int(s[:]+s[d-2::-1])
  p1_2 = bin(p1_10)[2:]
  if p1_2[:]==p1_2[::-1]:
    sum += p1_10 
    print p1_10    
  
  p2_10 = int(s[:]+s[::-1])
  p2_2 = bin(p2_10)[2:]
  if p2_2[:]==p2_2[::-1]:
    sum += p2_10
    print p2_10
    
  
for i in range(1,10):
  p2_2 = bin(i)[2:]
  if p2_2[:]==p2_2[::-1]:
    sum += i
    print i

print sum
    