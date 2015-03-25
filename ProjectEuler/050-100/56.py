"""
A googol (10^100) is a massive number: one followed by one-hundred zeros; 
100^100 is almost unimaginably large: one followed by two-hundred zeros. 
Despite their size, the sum of the digits in each number is only 1.

Considering natural numbers of the form, ab, where a, b < 100, 
what is the maximum digital sum?
"""

max_sum = 0
a0, b0, a1, b1 = [90,90,100,100]
for a in range(a0,a1):
  for b in range(b0,b1):
    s = str(a**b)
    sum = 0
    for i in s:
      sum += ord(i) - ord('0')
    if sum > max_sum: max_sum = sum
  
print max_sum





 