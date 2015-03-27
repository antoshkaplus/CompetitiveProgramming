
from math import sqrt


def gen(n):
  m = 0
  d = 1
  a = b = int(sqrt(n))
  while True:
    yield a 
    m = d*a-m
    d = (n-m*m)/d
    a = (b+m)/d
    
def eval(arr):
  num,den = 0,1
  for a in arr[:0:-1]:
    num += a*den
    num,den = den,num
  return num,den

res = 0  
T = 100-1
N = 100 
for n in range(1,N+1):
  a = sqrt(n)  
  if int(a) == a: continue
  c0 = '0'*T
  arr = []
  for k in gen(n):
    arr.append(k)
    num,den = eval(arr)
    c1 = str(num*10**T/den)
    #print c1,len(c1)
    if c1 == c0: 
      res += arr[0]+sum(map(int,c1))
      break
    c0 = c1
    
print res  
  


