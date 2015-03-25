
from math import sqrt

pals = []

def palindrom(numb):
  s = str(numb)
  n = len(s)
  print s, s[:n/2] == s[(n-1)/2+1::-1]
  return s[:n/2] == s[(n-1)/2+1::-1]

for i in xrange(1, 122):#10**7+1):
  s = str(i)
  s += s[::-1]
  p = int(s)
  r = int(sqrt(p))
  print p, r
  if r**2 == p and palindrom(r):
    pals.append(p)

f = open("test3.txt")
fout = open("out3.txt", "w")

print pals

s = f.read().split("\n")
T = int(s[0])
for i in range(1,T+1):
  a, b = map(int, s[i].split())
  n = len(filter(lambda x: a <= x <= b, pals))
  fout.write("Case #"+str(i)+": "+str(n)+"\n")