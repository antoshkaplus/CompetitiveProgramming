
import sys


T = int(raw_input())
for t in range(T):
    N = int(raw_input())
    ns = map(int, raw_input().split())
    s_1 = 0
    max_k = 0
    for i in range(1, len(ns)):
        k = ns[i-1] - ns[i]
        if k > 0: 
            if k > max_k: max_k = k
            s_1 += k
    s_2 = 0
    for i in range(len(ns)-1):
        s_2 += min(ns[i], max_k)
    
    print "Case #" + str(t+1) + ": " + str(s_1) + " " + str(s_2) 