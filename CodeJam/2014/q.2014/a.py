
f = open("input.txt")
strs = f.read().split("\n")
n_tests = int(strs[0])
for i_test in range(n_tests):
    i_start = i_test*10+1
    row_0 = int(strs[i_start])
    ns_0 = set(map(int, strs[i_start+row_0].split()))
    row_1 = int(strs[i_start+5])
    ns_1 = set(map(int, strs[i_start+5+row_1].split()))
    
    s = list(ns_0 & ns_1)
    print "Case #" + str(i_test+1) + ": ",
    if len(s) == 1: print s[0]
    elif len(s) > 1: print "Bad magician!"
    elif len(s) == 0: print "Volunteer cheated!"
    