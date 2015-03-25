"""
Take the number 192 and multiply it by each of 1, 2, and 3:

192 * 1 = 192
192 * 2 = 384
192 * 3 = 576
By concatenating each product we get the 1 to 9 pandigital, 
192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)

The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, 
giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be formed 
as the concatenated product of an integer with (1,2, ... , n) where n > 1?
"""

Q = [(9,range(1,10)),
     (4,range(10,100)),
     (3,range(100,1000)),
     (2,range(1000,10000))]
     
max_pan = 0     
     
seq_dream = [0]+[1 for i in range(9)]    
for q in Q:
  for i_q in q[1]: # integer numbers 
    seq = [0 for i in range(10)]
    numbs = [i_q*j for j in range(1,q[0]+1)]
    
    for j,n in enumerate(numbs):
      while n != 0:
        n,p = divmod(n,10)    
        seq[p] += 1
      if sum(seq) >= 9: break
    
    if seq == seq_dream: 
      max_pan = max(max_pan,int("".join(map(str,numbs[:j+1]))))
    
    

print max_pan  
  
  
  
  
  