
from heapq import * 
from math import ceil

"""
T = int(raw_input())
for t in range(T):
    D = int(raw_input())
    ps = map(lambda x: -int(x), raw_input().split())
    heapify(ps)
    res = -ps[0]
    for i in range(res):
        r = -heappop(ps)
        if r + i < res:
            res = r + i
        a = r/2
        heappush(ps, -a)
        heappush(ps, -(r - a))
    print "Case #" + str(t+1) + ":", res
	
# current solution won't work	
print 
print
"""

T = int(raw_input())
for t in range(T):
    D = int(raw_input())
    orig_ps = map(lambda x: int(x), raw_input().split())
    result = max(orig_ps)
    # max on plate
    for i in range(1, max(orig_ps)+1):
        ps = list(orig_ps)
        count = 0
        for p in ps:
            count += int(ceil(1. * p / i)) - 1
        if result > count + i:
            result = count + i
    print "Case #" + str(t+1) + ":", result
