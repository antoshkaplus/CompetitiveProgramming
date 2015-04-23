
T = int(raw_input())
for t in range(T):
    S_max, count = raw_input().split()
    S_max = int(S_max)
    count = map(int, count)
    sum = 0
    need = 0
    for i, c in enumerate(count):
        if sum < i:
            need += i - sum
            sum += i - sum
        sum += c
    print "Case #" + str(t+1) + ": " + str(need) 