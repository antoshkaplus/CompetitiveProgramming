"""
The 5-digit number, 16807=7^5, is also a fifth power. 
Similarly, the 9-digit number, 134217728=8^9, is a ninth power.

How many n-digit positive integers exist which are also an nth power?
"""

res = 0
# n^i
for n in range(1,10):
  i = 1
  p = n
  while True:
    k = len(str(p))
    if k != i: break
    print p,i
    res += 1
    
    p*=n; i+=1
    
print res