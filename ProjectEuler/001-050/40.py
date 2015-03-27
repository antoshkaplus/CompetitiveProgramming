

pos = [10**i for i in range(7)]

prod = 1

for n in pos: 
  rank = 1
  while True:
    k = rank*9*(10**(rank-1))
    if n-k > 0: 
      rank+=1
      n-=k
    else: break
    
  if n%rank == 0:   
    d,m = n/rank, rank-1  
  else:
    d,m = n/rank+1, n%rank
  print d,m,rank
  print str(10**(rank-1)+d-1)[m-1]
  prod *= int(str(10**(rank-1)+d-1)[m-1])  
  
print prod