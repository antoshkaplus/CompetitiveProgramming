
from heapq import *

T = int(raw_input())
D = int(raw_input())
ps = map(int, raw_input().split())
res = -ps[0]
for i in range(res):
    r = heappop(ps)
    if r > res:
        res = r