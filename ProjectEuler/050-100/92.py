
N = 7

def fact(n):
  s = 1
  for c in range(2,n+1): s *= c
  return s
  
f = [fact(i) for i in range(N+1)]
s = [i**2 for i in range(10)]

def perm(n,arr):
  return f[n]/reduce(lambda x,y: x*y,(f[a] for a in arr))

def gen(k,n):
  arr = n*[0]
  arr[n-1] = k
  yield arr[:]
  while arr[0] != k:
    i = n-1
    while arr[i] == 0: i -= 1
    arr[i-1] += 1
    arr[i] -= 1
    arr[n-1],arr[i] = arr[i],arr[n-1]
    yield arr[:]
    
p = 570*[None]    
p[1] = False
p[89] = True
  
result = 0    
for arr in gen(N,10):
  if arr[0] == N: continue
  r = sum(a*s[i] for i,a in enumerate(arr))
  q = []
  while p[r] == None: 
    q.append(r)
    r = sum(s[i] for i in map(int,str(r)))
  for c in q: p[c] = p[r]
  if p[r]:
    result += perm(N,arr)
  
print result