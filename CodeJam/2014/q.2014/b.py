f = open("input.txt")
strs = f.read().split("\n")
n_tests = int(strs[0])
for i_test in range(1, n_tests+1):
    C, F, X = map(float, strs[i_test].split())
    
    time = X/2
    time_next = 0
    time_on_factories = 0
    factory_count = 0
    while True:
        time_on_factories += C/(factory_count*F + 2)
        factory_count += 1
        time_next = time_on_factories + X/(factory_count*F + 2)
        if time_next > time: break
        time = time_next
       
    print "Case #" + str(i_test) + ": " + str(time) 
   