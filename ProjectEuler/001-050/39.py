"""
If p is the perimeter of a right angle triangle with integral length sides, 
{a,b,c}, there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value of p <= 1000, is the number of solutions maximised?
"""

import math

seq = [0 for i in range(1000)]

for i in range(1,499):
  for j in range(i,499-i):
    p = i*i+j*j
    r = math.sqrt(p)
    if r == int(r) and r+i+j <= 1000:
      seq[int(r)+i+j-1] += 1

r = 0      
for i,p in enumerate(seq):
  if p > seq[r]: r = i      
     
print r+1     