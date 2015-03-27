

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


n = len(mat) 

m = 0 # max res value
for i in range(n):
  for j in range(n):
    m += mat[i][j]

res = [mat[k][0] for k in range(n)]

for j in range(n-1):
  buf = n*[m]
  for i in range(n): # start row
    for k in range(n): # finish row
      c = res[i]+mat[k][j+1]
        
      if i != k:
        b1,b2 = (k,i) if i > k else (i+1,k+1)
        c += sum(mat[k1][j] for k1 in range(b1,b2))
          
      if buf[k] > c: buf[k] = c
  res = buf   
  
  
print min(res)  
  

  

