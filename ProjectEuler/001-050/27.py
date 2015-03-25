"""
Euler published the remarkable quadratic formula:
n**2 + n + 41

It turns out that the formula will produce 40 primes 
for the consecutive values n = 0 to 39. However, when n = 40, 
402 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, 
and certainly when n = 41, 41**2 + 41 + 41 is clearly divisible by 41.

Using computers, the incredible formula  n**2 - 79n + 1601 was discovered, 
which produces 80 primes for the consecutive values n = 0 to 79. 
The product of the coefficients, -79 and 1601, is -126479.

Considering quadratics of the form:
n**2 + an + b, where |a| < 1000 and |b| < 1000,
where |n| is the modulus/absolute value of n
e.g. |11| = 11 and |4| = 4

Find the product of the coefficients, a and b, 
for the quadratic expression that produces the maximum number 
of primes for consecutive values of n, starting with n = 0.
"""

# returns list of primes in segment [1:n]
# table[i] = is (i+1) prime
def get_prime_table(n):  
  table = n*[True]
  table[0] = False
  for i, el in enumerate(table):
    if el: table[2*i+1:n:i+1] = len(table[2*i+1:n:i+1])*[False]
  return table

a_max = 999    
    
prime_bound = 79**2 + a_max*79 + a_max  
  
prime_table = get_prime_table(prime_bound)

b_coeff = [i+1 for i,p in enumerate(prime_table[:a_max]) if p]  
  
k_max = 0  
for a in range(-999,999+1):
  for b in range(-999,999+1):
    k = 0
    while True:
      p = k*k + a*k + b
      if not prime_table[p-1]: break
      k+=1
      if k == 71: print a,b
    if k > k_max: k_max = k 
  
print k_max  
  
  
  