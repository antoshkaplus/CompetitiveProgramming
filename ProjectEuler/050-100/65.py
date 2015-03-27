

n = 100
p = n*[1]
p[0] = 2

for k,i in enumerate(range(2,n,3)):
  p[i] = 2*(k+1)


num = p[n-1]
den = 1
for i in range(n-2,-1,-1):
  num,den = p[i]*num+den,num
  
print sum(map(int,list(str(num))))
