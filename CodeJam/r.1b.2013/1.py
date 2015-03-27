
s = open("A-large-practice.in").read().split("\n")
out = open("out.txt", "w")
T = int(s[0])
for t in range(T):
  A, N = map(int, s[2*t+1].split())
  arr = sorted(map(int, s[2*t+2].split()))
  i = 0 # how many did I absorb
  j = 0
  r = range(N, -1, -1) # moves to do to get win the game on i state
  while i < N and j < N:
    if A <= arr[i]:
      j += 1
      A += A-1
    else:
      r[i+1] += j
      A += arr[i]
      i += 1
  k = min(r[:i+1])
  out.write("Case #"+str(t+1)+": "+str(k)+"\n")