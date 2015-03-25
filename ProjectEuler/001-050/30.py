""" 
Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

1634 = 1^4 + 6^4 + 3^4 + 4^4
8208 = 8^4 + 2^4 + 0^4 + 8^4
9474 = 9^4 + 4^4 + 7^4 + 4^4
As 1 = 1^4 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
"""

pow = 5
dig_vals = [i**pow for i in range(10)]

num_min = 2**pow; i = len(str(num_min))
n_min = i

num_max = 9**pow; i = 1
while len(str(i*(9**pow))) >= i: i+=1
i-=1
n_max = i

# table[k][p] - k - rank, p - digit
table = [[p*(10**k) for p in range(10)] for k in range(n_max)]

pdi_nums = []

dig_max = 2
# n - number of ranks
for n in range(n_min,n_max+1):
  # try to increase number of possible digits
  j = dig_max+1
  while j != 10 and len(str(dig_vals[j])) <= n: j += 1
  dig_max = j-1
  
  # computing 
  num = [0 for k in range(n)]
  num[0] = 1
  while True:
    # start num position
    k = n-1
    # finding rank to increase
    while k >= 0 and num[k] == dig_max: k-=1
    if k == -1: break
    
    num[k]+=1
    
    for i in range(k+1,n): num[i] = 0
    
    res_num = 0
    res_pow = 0
    for i,d in enumerate(num):
      res_num += table[n-1-i][d] 
      res_pow += dig_vals[d]
      
    if res_num == res_pow: 
      pdi_nums.append(res_num)
      print num,n,res_num    

    
print sum(pdi_nums)








