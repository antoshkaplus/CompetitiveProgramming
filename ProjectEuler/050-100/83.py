
from collections import deque


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

"""
n = len(mat) 
 
field = [[None]*n for i in range(n)]

stack = deque()

def go(v,p):
  i,j = p
  m,f = mat[i][j],field[i][j]
  if f == None or v+m < f:
    field[i][j] = v+m
  else:
    return 
    
  f = field[i][j]
  if i > 0:
    stack.append((f,(i-1,j)))
  if i < n-1:
    stack.append((f,(i+1,j)))
  if j > 0:
    stack.append((f,(i,j-1)))
  if j < n-1:
    stack.append((f,(i,j+1)))
    
k = 0    
stack.append((0,(0,0)))
while stack:
  k += 1
  go(*stack.popleft())

print k
print field[-1][-1]


"""
def main():
  global mat
  array = mat # the matrix
  MAX_VALUE = sum(map(sum, array))
  length = len(array)
  result = [[MAX_VALUE for _ in xrange(length)] for _ in xrange(length)]
  result[0][0] = array[0][0]

  k = 0
  while True:
    k += 1
    change = False
    for i in xrange(length):
      for j in xrange(length):
        min_value = min(i and result[i - 1][j] or MAX_VALUE,
                        i + 1 - length and result[i + 1][j] or MAX_VALUE,
                        j and result[i][j - 1] or MAX_VALUE,
                        j + 1 - length and result[i][j + 1] or MAX_VALUE)
        if min_value + array[i][j] < result[i][j]:
          change = True
          result[i][j] = min_value + array[i][j]
    if not change:
      break
  print result[-1][-1]
  print k
  
main()  

