
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

# pr_divs are primes such that less or equal sqrt(n)
def is_prime(n,pr_divs):
  res = True
  for p in pr_divs:
    if n%p == 0: res = False; break
  return res
      
      

     