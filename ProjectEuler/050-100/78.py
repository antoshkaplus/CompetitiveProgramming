"""
partition = [[1]] # p[0]=1  
n = 10**6
k = 0
while partition[-1][-1]%n != 0:
  k += 1

  part = (k+1)*[0]
  for p in range(1,k+1):
    s = len(partition[k-p])
    part[p] = part[p-1] + partition[k-p][min(s-1,p)]
  partition.append(part)
 
print k
"""

from math import sqrt

N = 10**6  

numbs = [1,1]
def P(n):
  res = 0
  b = 1
  for k in range(1,int(1+sqrt(24*n+1))/6+1):
    res += b*numbs[n-k*(3*k-1)/2]
    b *= -1
  b = 1
  for k in range(1,int(-1+sqrt(24*n+1))/6+1):
    res += b*numbs[n-k*(3*k+1)/2]
    b *= -1
  return res%N
  
k = 1
while numbs[-1] != 0:
  k+=1  
  numbs.append(P(k))
  
print k
  
  