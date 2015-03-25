
#S = 18
S = 2*10**6
R = None  
A = None
def check(i,j,p):
  global R
  global A
  if R == None or abs(S-R) > abs(S-p):
    R = p  
    A = (i,j)
    
i, j = 1, 1    
while True:
  j = 1
  p = i*(i+1)/2
  prev = None
  cur = p
  while cur < S:
    j+=1
    prev = cur
    cur = cur+j*p 
  check(i,j-1,prev)
  check(i,j,cur)
  if i > j: break
  i+=1 

print A, A[0]*A[1]




