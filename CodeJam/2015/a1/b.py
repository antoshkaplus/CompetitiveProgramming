
import sys



# brute force solution
def find_barber(B, N, M):
    st = B*[0]
    while 


T = int(raw_input())
for tt in range(T):
    B, N = map(int, raw_input().split())
    M = map(int, raw_input().split())
    t = 0
    for m in M:
        t += 1./m
    t = (N -1) / t
    # t = when finish with N-1 customer
    t = int(t)
    ns = [ t / m for m in M ]
    st = [ n*m for n, m in zip(ns, M) ]
    n = sum(ns)
    I = None
    while True:
        s = None
        I = -1 
        for i, t in enumerate(st):
            if s == None or t < s or (t == s and i < I): 
                I = i
                s = t
        st[I] += M[I]
        n += 1
        if n == N: break
    print "Case #" + str(tt+1) + ": " + str(I+1) 