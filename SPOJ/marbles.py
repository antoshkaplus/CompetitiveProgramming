 
from math import * 
 
def permutations_with_repetitions(n, k): 
    if k > n-k: k = n-k
    ans = 1
    for i in range(k):
        ans = ans*(n-i)/(i+1)
    return ans
 
t = int(raw_input())
for i in range(t):
    n, k = map(int, raw_input().split())
    print permutations_with_repetitions(n-1, k-1)
   