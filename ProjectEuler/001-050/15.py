"""
Starting in the top left corner of a 2x2 grid, there are 6 routes (without backtracking) 
to the bottom right corner.

How many routes are there through a 20x20 grid?
"""

# permutations with repetition of arrows...

def factorial(n):
  result = 1
  for i in range(1,n+1): result *= i
  return result
  
n = 20  
print factorial(n+n)/(factorial(n)*factorial(n))  
  