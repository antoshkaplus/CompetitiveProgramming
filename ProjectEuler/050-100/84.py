from math import ceil

N = 6
P = 2*N*[0]
for i in range(2,2*N+1):
  P[i-1] = min(N,i-1)-ceil(i/2.)+1
s = sum(P)
for i in range(2*N):
  P[i] /= s
q = (N-1.)*(1.-35./(40*16))**2/N**5.
for i in range(2,2*N+1,2):
  P[i-1] -= q
P[0] = q*N

print P

print sum(P)

# 10 - Jail

eps = 0.1**9
n = 40
x0 = n*[0.025]
while True:
  x1 = n*[0.]
  # finding x1   
  for i in range(0,n):
    for j in range(2,2*N+1):
      k = (i+j+1)%n-1
      x1[k] += P[j-1]*x0[i]
    x1[10] += P[0]*x0[i]
  
  # chance is first !!!
  for i in [7,22,36]:
    r = 2*[{7:15,22:25,36:5}[i]]+[{7:12,22:28,36:12}[i]]
    r += [0,10,11,24,39,5,i-3]
    for j in r:
      x1[j] += x1[i]/16
    x1[i] *= 3./8 
    
  for i in [2,17,34]:
    x1[10] += x1[i]/16
    x1[0] += x1[i]/16
    x1[i] *= 7./8
 
  x1[10] += x1[30]
  x1[30] = 0.
   
  if max(abs(e0-e1) for e0,e1 in zip(x0,x1)) < eps:
    break
  
  x0 = x1
   
   
print    
for i,x in enumerate(x1):
  print i,":",int(x*10000),", ", 
   