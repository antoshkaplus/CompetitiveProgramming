
from math import *

def period(N):
  n = int(sqrt(N))
  a = a0 = n
  b = b0 = n
  c = c0 = 1
  k = 0
  while True:
    c = (N-b**2)/c
    a = (n+b)/c # use if need period numbers
    b = a*c - b
    k += 1
    if b == b0 and c == c0:
      break
  return k
    
    
k = 0    
for i in range(2,10000):
  if sqrt(i) != int(sqrt(i)) and period(i)%2 != 0:
    k += 1     
print k