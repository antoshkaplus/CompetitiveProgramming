"""
If we list all the natural numbers below 10 that are multiples of 3 or 5, 
we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
"""

n = 999

i3 = n/3
i5 = n/5

sum3 = 3*i3*(i3+1)/2
sum5 = 5*i5*(i5+1)/2

i35 = n/(3*5)
sum35 = 3*5*i35*(i35+1)/2

sum = sum3 + sum5 - sum35

print sum3, sum5, i3, i5

print sum