

def printOptions(options):
    for opt in options:
        print opt


T = int(raw_input()) 
for i_test in range(1, T+1):
    N, L = map(int, raw_input().split())
    #print N, L
    read = lambda: map(lambda x: map(int, x), raw_input().split())
    outlets = read()
    devices = read()
    options = []
    for out_i in range(N):
        for dev_i in range(N):
            inds = []
            options.append((out_i, dev_i, inds))
            for i in range(L):
                if outlets[out_i][i] != devices[dev_i][i]:
                    inds.append(i)
    # sort by indices
    options.sort(key = lambda x: x[2])                
    #printOptions(options)
    prev = (None, None, None)
    min = L+1
    for opt in options:
        if prev[2] != opt[2]:
            prev = opt
            n = 1
        else:
            n += 1
        if n == N:
            if len(opt[2]) < min:
                min = len(opt[2])
     
    result = "NOT POSSIBLE"
    if min != L+1:
        result = str(min)
    print "Case #" + str(i_test) + ": " + result


