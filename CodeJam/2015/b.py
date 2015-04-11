
from heapq import * 

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