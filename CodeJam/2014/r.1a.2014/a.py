
def count(ss, ch, i):
    k = 0
    for s in ss:
        if s[i] == ch:
            k+=1
    return k


s = open("input.txt").read().split("\n")
T = int(s[0])
for i_test in range(1,T+1):
    N, L = map(int, s[i_test*3 - 2].split())
    outlets = map(lambda x: map(int, x), s[i_test*3-1].split())
    devices = map(lambda x: map(int, x), s[i_test*3].split())
    
    is_possible = True
    n_switches = 0
    
    future_stack = []
    stack = [(0, N)]
    for i in range(L):
        while stack and is_possible:
            a, b = stack.pop()
        
            out = count(outlets[a:b], 0, i)
            dev = count(outlets[a:b], 0, i)
            future_stack.append((a, a + out))
            future_stack.append((a + out, b))
            print i, a, b, out, dev
            if (out == dev):
                outlets[a:b] = sorted(outlets[a:b], key=lambda x: x[i])
                devices[a:b] = sorted(devices[a:b], key=lambda x: x[i])
            elif (L - out == dev):
                outlets[a:b] = sorted(outlets[a:b], key=lambda x: x[i])
                devices[a:b] = sorted(devices[a:b], key=lambda x: -x[i])
                n_switches += 1
            else:
                is_possible = False
                break
                print "NOT POSSIBLE"
            print outlets
            print devices
        stack = future_stack
        future_stack = []
        
        if not is_possible:
            break
    
    print "Case #" + str(i_test) + ": ",
    if not is_possible:
        print "NOT POSSIBLE"
    else:
        print n_switches
    
    
    
    
    
    
    
    







