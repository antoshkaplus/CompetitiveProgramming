"""
A unit fraction contains 1 in the numerator. The decimal representation of the unit 
fractions with denominators 2 to 10 are given:
1/2	= 0.5
1/3	= 0.(3)
1/4	= 0.25
1/5	= 0.2
1/6	= 0.1(6)
1/7	= 0.(142857)
1/8	= 0.125
1/9	= 0.(1)
1/10= 0.1
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. 
It can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
"""

# error !!! i'm finding longest cycle, not !!!d!!! at all


import sys
sys.stdout = open("26.txt","w")

def find_cycle(s):
  # repeating to make sure that's cycle
  r = 5
  res = 0
  ls = len(s)
  
  i = 1
  while True:
    r = (3 if i > 30 else 30-i+3)
    if r*i > ls: break # early do resume 
    flag = True
    for j in range(1,r):
      if s[ls-i*j:ls-i*(j-1)]!=s[ls-i*(j+1):ls-i*j]:
        flag = False
        break
    if flag:
      res = i
      break
    i+=1
    
  return res

max_cycle = 0
for div in range(1,1000): 
  numb = 1
  s = ""
  while True:
    numb *= 10
    while numb/div < 1:
      numb *= 10
      s += '0'
    res = numb/div
    s += str(res)
    numb %= div
    if numb == 0: break
    else:
      cycle = find_cycle(s)
      if cycle:
        if div == 983:
          print cycle,"\n",s,"\n",s[len(s)-cycle:len(s)],"\n"
        if cycle > max_cycle: 
          max_cycle = cycle
           
        break
  
print max_cycle      
      
      
      
      

    
    
    
    

