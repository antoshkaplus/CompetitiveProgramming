
import math

n_min = 1
n_max = 100
bound = 10**6

combs = 0

n = n_max
n_fact = math.factorial(n)
while n_fact > bound:  
  n_even = True if n%2==0 else False
  
  r_st = n//2
  r = r_st
  
  r_fact_r = math.factorial(r)
  r_fact_d = math.factorial(n-r)
  while n_fact/(r_fact_r*r_fact_d) > bound:
    # decrease factorial of r
    r_fact_r//=r
    # increase factorial of n-r
    r_fact_d*=n-r+1
    r-=1    
    
  if r!=r_st: combs += 2*(r_st-r-1)+1 if n_even else 2*(r_st-r)
  
  n_fact//=n
  n-=1
  
print combs
  