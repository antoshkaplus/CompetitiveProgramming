

from math import sqrt

n = int(raw_input())

lower_bound, upper_bound = [], []
for i in range(n) : 
  a = raw_input().split()
  lower_bound.append(int(a[0]))
  upper_bound.append(int(a[1]))

def find_primes(bound) :
  primes = [True]*bound
  primes[0] = False
  
  result = []
  for i in range(1,bound+1) :
    if primes[i-1]:
      result.append(i)
      primes[2*i-1:bound:i] = [False]*len(primes[2*i-1:bound:i])
  return result

primes = find_primes(int(sqrt(max(upper_bound))))  

def find_greatest_divisor(number,divs) : 
  """ Finds divisor index, that can divide by number """
  result = None
  
  s = sqrt(number)
  if len(divs) and divs[0] <= s:
    a = 0; b = len(divs)-1
    while True :
      if b - a <= 1 :      
        result = (a if divs[b] != s else b);
        break
      c = (a+b)/2
      if divs[c] >= s :
        b = c
      else : # divs[c] < s  
        a = c
            
  return result
            
indexes = [find_greatest_divisor(x,primes) for x in upper_bound]

result = ''  

for i in range(n) :
  lb = lower_bound[i] 
  ub = upper_bound[i]
  
  dist = ub-lb+1
  interval = [True]*dist
  if lb == 1 : interval[0] = False
  if indexes[i] != None :   
    for k in primes[:indexes[i]+1] :
      start_pos = (2*k - lb if k >= lb else (k - lb % k) % k)
      interval[start_pos:dist:k] = [False]*len(interval[start_pos:dist:k])
    for k, b in enumerate(interval) :
      if b : result += str(k+lb) + '\n'
    
  result += '\n' 

print result


