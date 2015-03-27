
def pow(a,p):
  if p == 1: 
    c = a
  else:
    c = pow(a,p/2)
    c *= c
    if p%2:
      c *= a
      
  return int(str(c)[-10:])
  

print str(28433*pow(2,7830457)+1)[-10:]