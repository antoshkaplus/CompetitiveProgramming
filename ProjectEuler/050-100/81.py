

mat = []
for s in open("matrix.txt"):
  mat.append(map(int,s.split(",")))
"""
mat = [[131,673,234,103,18 ],
       [201,96 ,342,965,150],
       [630,803,746,422,111],
       [537,699,497,121,956],
       [805,732,524,37 ,331]]
"""  
  
def gen(n):
  for k in range(0,n):
    for q in range(0,k+1):
      yield (k-q,q)
  for k in range(n,1,-1):
    for q in range(1,k):
      yield (q-k,-q)
  
n = len(mat)
for (i,j) in gen(n):    
  #print (i,j)
  b1 = b2 = False
  if i != 0 and i != -n:
    b1 = True
    v1 = mat[i-1][j]
  if j != 0 and j != -n: 
    b2 = True
    v2 = mat[i][j-1]
  
  
  if b1 and b2:
    mat[i][j] += min(v1,v2)
  elif b1: 
    mat[i][j] += v1
  elif b2: 
    mat[i][j] += v2
    
print mat[n-1][n-1]    
    
    
    