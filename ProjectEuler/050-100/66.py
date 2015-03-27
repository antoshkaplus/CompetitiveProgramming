
from math import *

# continued fraction - cf 

def gen_cf(N):
  n = int(sqrt(N))
  a = a0 = n
  b = b0 = n
  c = c0 = 1
  k = 0
  while True:
    yield a
    c = (N-b**2)/c
    a = (n+b)/c # use if need period numbers
    b = a*c - b
    
    
def cf_to_f(cf):
  n = len(cf)
  num = cf[n-1]
  den = 1
  for i in range(n-2,-1,-1):
    num,den = cf[i]*num+den,num
  return num,den
  
res = []  
numbs = filter(lambda x: sqrt(x)!=int(sqrt(x)),range(2,1000))  
c = []
for i in numbs:
  c = []
  for n in gen_cf(i):
    c.append(n)
    x,y = cf_to_f(c)
    if x**2 - i*y**2 == 1:
      res.append((x,i))
      break
      
r = max(res,key=lambda x: x[0])
print r[1]


