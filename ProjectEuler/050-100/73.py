
"""
def gcd(a,b):
  while a != b:
    a,b = (a-b,b) if a > b else (a,b-a)  
  return a

s = 0
n = 12
for i in range(2,n+1):
  st = 2*i
  fh = 3*i
  if fh > n:
    fh = n+1
  if st > n:
    break
  s += fh-st-1
  for j in range(st+1,fh):
    if gcd(i,j) > 1:
      s -= 1
  
print s
"""

n0 = 2
n = 12000

p_arr = [set() for i in range(n)]

b_arr = n*[False]
b_arr[0] = True
for i,b in enumerate(b_arr):
  if not b:
    for j in range(i,n,i+1):
      p_arr[j].add(i+1)
      b_arr[j] = True

s = 0  
for i in range(n0,n+1):
  st = 2*i
  fh = 3*i
  if fh > n:
    fh = n+1
  if st > n:
    break
  s += fh-st-1
  arr = [False]*(fh-st-1)
  for p in p_arr[i-1]:
    r = st%p
    arr[-r+p-1::p] = [True]*len(arr[-r+p-1::p])
  s -= arr.count(True)
  
print s


