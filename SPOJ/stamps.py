T = int(raw_input())
for t in range(T):
    need, friends = map(int, raw_input().split(" "))
    marks = map(int, raw_input().split(" "));
    marks.sort(reverse=True)
    # need borrow anyway
    borrowed = 0
    for v in marks:
    	need -= v
    	borrowed += 1
    	if need <= 0:
    		break

    print "Scenario #" + str(t+1) + ":"
    if need > 0:
        print "impossible"
    else:
        print borrowed
    print
