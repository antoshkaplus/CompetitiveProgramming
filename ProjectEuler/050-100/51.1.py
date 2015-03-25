import math

m = 8
pp = []
ppp = {}
k = 1
n = 2

found = False

while not found:
    mink = 10 ** (k - 1)
    maxk = 10 ** k

    ppp[k] = []

    maxksqrt = int(math.sqrt(maxk))
    ppx = []
    for p in pp:
        if p <= maxksqrt:
            ppx.append(p)

    while n < maxk:
        for p in ppx:
            if n % p == 0:
                break
        else:
            pp.append(n)
            ppp[k].append(n)
            if n <= maxksqrt:
                ppx.append(n)
            
        n += 1

    for p in ppp[k]:
        s = str(p)
        for c in '0123456789':
            if s.count(c) == 0:
                continue
            ss = []
            ss.append(p)
            for r in '0123456789':
                if r == c:
                    continue
                s1 = s.replace(c, r)
                if ppp[k].count(int(s1)) > 0:
                    ss.append(int(s1))
            if len(ss) >= m:
                found = True
                print ss
                break
        if found:
            break

    print k
    k += 1

