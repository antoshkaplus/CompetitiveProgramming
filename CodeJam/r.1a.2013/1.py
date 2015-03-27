
from math import sqrt, pi

f = open("A-large-practice.in")
out1 = open("out1.txt", "w")
s = f.read().split("\n")

T = int(s[0])
for i in range(1,T+1):
  r, t = map(int, s[i].split())
  n = int((1.-2.*r+sqrt((2.*r-1.)**2 + 8.*t))/4.)
  while 2*(n+1)**2 + (n+1)*(2*r-1) <= t: n+=1
  while 2*n**2 + n*(2*r-1) > t: n-=1
  out1.write("Case #"+str(i)+": "+str((n))+"\n")
  print i