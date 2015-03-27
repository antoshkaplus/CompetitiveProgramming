"""
It can be seen that the number, 125874, and its double, 251748, 
contain exactly the same digits, but in a different order.

Find the smallest positive integer, x, such that 
2x, 3x, 4x, 5x, and 6x, contain the same digits.
"""

def get_pattern(x,base):
  p = base*[0]
  while x != 0:
    x,m = divmod(x,base)
    p[m] += 1
  return p  

res = None  
  
m_min = 2
m_max = 6
base = 10
p = 1
while True:
  flag = True
  pat = get_pattern(m_min*p,base)
  for i in range(m_min+1,m_max+1):
    if pat != get_pattern(i*p,base):
      flag = False 
      break
  if flag: 
    res = p
    break
  p+= 1
    
print res