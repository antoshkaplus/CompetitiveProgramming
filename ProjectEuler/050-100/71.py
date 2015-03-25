
def gcd(a,b):
  while not (a==b):
    if a>b: a-=b
    else: b-=a
  return a
  
print gcd(428570,999999)
   