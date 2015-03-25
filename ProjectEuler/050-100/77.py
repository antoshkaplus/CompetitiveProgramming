
primes = []

def is_prime(k):
  res = False
  for p in primes:
    if k%p == 0: break
  else: 
    res = True  
  return res
  
partition = [[1],[0]] # p[0]=1, p[1]=0  
n = 5000
k = 1 
while partition[-1][-1] <= n:
  k += 1
  
  if is_prime(k): 
    primes.append(k)
  
  part = (len(primes)+1)*[0]
  for i,p in enumerate(primes):
    s = len(partition[k-p])
    part[i+1] = part[i] + partition[k-p][min(s-1,i+1)]
  partition.append(part)
 
print k


    
  