
"""
1 - 0
i - 1
j - 2
k - 3
"""

# is signed (minus exists)
M = [[(False, 0), (False, 1), (False, 2), (False, 3)],
     [(False, 1), (True , 0), (False, 3), (True , 2)],
     [(False, 2), (True , 3), (True , 0), (False, 1)],
     [(False, 3), (False, 2), (True , 1), (True , 0)]]
     
CH_TO_NUMB = {"1":0, "i":1, "j":2, "k":3}     

def Mult(m_0, m_1):
    n = M[m_0[1]][m_1[1]]
    n = ((map(lambda x: x[0], (n, m_0, m_1)).count(True) % 2 == 1),
         n[1])
    return n

def Next(s, i):
    return (False, CH_TO_NUMB[s[i%len(s)]])

# checks if arguments add up to -1 
# s - string of chars
# x - how many times repeated
def MultiplyAll(s, x):
    k = x%4
    u = (False, 0)
    for i_k in range(k):
        for ch in s:
            u = Mult(u, (False, CH_TO_NUMB[ch]))
            #print u 
    return u == (True, 0)

# if i == end - didn't find
def FindInRange(key, st, end, s):
    u = (False, 0)
    found = False
    for i in range(st, end):
        u = Mult(u, Next(s, i))
        if u == key:
            break
    else:
        i += 1
    return i


def ConstructIJ(s, x):
    N = 4*len(s)
    st = 0
    end = min(st+N, x*len(s))
    i = FindInRange((False, 1), st, end, s)
    if i == end: return False
    st = i+1
    end = min(st+N, x*len(s))
    i = FindInRange((False, 2), st, end, s)
    if i == end: return False
    return True    

if __name__ == "__main__":
    T = int(raw_input())
    for t in range(T):
        # L - number of characters in string
        # X - number of repetitions
        L, X = map(int, raw_input().split())     
        
        
        s = raw_input()
        
        b = MultiplyAll(s, X) and ConstructIJ(s, X)
        #b = "".join([s for i in xrange(X)])
        
        res = "YES" if b else "NO"
        print ("Case #%d: %s" % (t+1, res)) 



    


            