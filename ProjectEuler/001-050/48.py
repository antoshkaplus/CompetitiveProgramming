"""
The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

Find the last ten digits of the series, 
1^1 + 2^2 + 3^3 + ... + 1000^1000.
"""

def power(x,i,p):
  """ x - number
      i - power
      p - quantity of positions of answer """
  q = []
  while i != 1:
    if i%2==0: 
      r = 1    
      i/=2
    else:
      r = 0
      i-=1
    q.append(r)
    
  res = x
  for r in q[::-1]:
    res*= res if r else x
    res = int(str(res)[-p:])
    
  return res


d = 10
b = 1000
res = 0
for i in range(1,b+1):
  res+=power(i,i,d)
  
print str(res)[-d:]




  