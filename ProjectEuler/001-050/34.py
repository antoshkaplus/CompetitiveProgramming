"""
145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the 
sum of the factorial of their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.
"""

def f(a):
  r = 1
  for i in range(2,a+1): r*=i
  return r
  
fd = [f(i) for i in range(10)]

max_fd = fd[9]

# finding n - max qnty of digits in number
n = 0
while len(str(n*max_fd)) >= n: n+=1
n-=1         
print n  
big_sum = 0  
# number of digits  
nd = 10
# counting
n_min = 2
for i in range(n_min,n+1):
  seq = [0 for j in range(nd-1)]+[i]  
  while True:
    d = nd-1
    
    s = 0
    for i_el,el in enumerate(seq):
      s += el*fd[i_el]
    
    sum_seq = nd*[0]
    for el in map(int,str(s)):
      sum_seq[el]+=1
    
    if seq == sum_seq:
      big_sum += s
      print seq,sum_seq,s 
    
    while d != 0:
      if seq[d] != 0:
        seq[d-1]+=1
        seq[d]-=1
        seq[d:] = (len(seq[d:])-1)*[0]+[sum(seq[d:])]
        break
      d-=1
      
    if d == 0: break # finished  
      
print big_sum





    
  
  
  
  
  
  
  
  
  
  




