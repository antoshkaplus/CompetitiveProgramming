"""
A number n is called deficient if the sum of its proper divisors 
is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, 
the smallest number that can be written as the sum of two abundant 
numbers is 24. By mathematical analysis, it can be shown that all 
integers greater than 28123 can be written as the sum of two abundant 
numbers. However, this upper limit cannot be reduced any further 
by analysis even though it is known that the greatest number that 
cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum 
of two abundant numbers.

Every integer greater than 20161 can be written as the sum of two abundant numbers.
"""

bound = 20161

# begin finding abundant numbers 

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

abundants = [i+1 for i in range(bound) if sums[i] > i+1]  
  
# end abundant numbers

print "here"

is_sum_of_two_abundants = bound*[False]
for i,a in enumerate(abundants):
  for b in abundants[i:]:
    if a+b <= bound:
      is_sum_of_two_abundants[a+b-1] = True
    else: break

print "here"
    
print sum([i+1 for i,val in enumerate(is_sum_of_two_abundants) if not val])













