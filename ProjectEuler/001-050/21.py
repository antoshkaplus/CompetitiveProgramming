"""
Let d(n) be defined as the sum of proper divisors of n 
(numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a _neq_ b, then a and b are an amicable pair and 
each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; 
therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
"""

from math import sqrt

# returns list of primes in segment [1:n]
def find_primes(n):
  primes = []
  table = n*[True]
  table[0] = False
  for i, el in enumerate(table):
    if el: 
      primes.append(i+1)  
      table[2*i+1:n:i+1] = len(table[2*i+1:n:i+1])*[False]
  return primes


# add divisor to set  
def add_divisor(res,key,val):
  if key in res: res[key]+=val
  else: res[key] = val  
  
# add divisors from divs {prime:quantity} dictionary to res     
def add_divisors(res,divs):  
  for key,val in divs.items(): add_divisor(res,key,val)

# returns list dictionary of {prime:quantity}
def find_prime_divisors(bound,primes):
  table = [{} for i in range(bound)]
  for i in range(bound):
    b = int(sqrt(i+1))
    div = 0
    for p in primes:
      if b < p: break
      if (i+1)%p == 0:
        div = p
        break
    if div:
      add_divisor(table[i],div,1)
      if len(table[(i+1)/div-1]) == 0: add_divisor(table[i],(i+1)/div,1)
      else: add_divisors(table[i],table[(i+1)/div-1])
  return table

bound = 10000
primes = find_primes(int(sqrt(bound)))
table = find_prime_divisors(bound,primes)

def sum_of_divisors(divs):
  sum = 1
  for div,quantity in divs.items():
    sum *= (1-div**(quantity+1))/(1-div)
  return sum
  
  
sums = bound*[0]
for i in range(bound):
  sums[i] = sum_of_divisors(table[i])
  if table[i] != {}: sums[i] -= i+1
 
  
double_amicable_sum = 0
for i,el in enumerate(sums):
  if el-1 <= bound and sums[el-1] == i+1 and el != i+1:
    double_amicable_sum += el+i+1
    print el, i+1
    
print double_amicable_sum/2


