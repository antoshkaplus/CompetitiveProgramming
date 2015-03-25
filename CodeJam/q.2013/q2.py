

fout = open("out2.txt", "w")
f = open("B-large.in")
s = f.read().split("\n")
T = int(s[0])
N, M = 0, 0
k = 0
for t in range(T):
  k += N+1
  N, M = map(int, s[k].split())
  lawn = map(lambda x: map(int, x.split()), s[k+1:k+1+N])
  rs = N*[0]
  cs = M*[0]
  for i in range(N):
    for j in range(M):
      if lawn[i][j] > rs[i]: rs[i] = lawn[i][j]
      if lawn[i][j] > cs[j]: cs[j] = lawn[i][j]
  res = "YES"
  for i in range(N):
    for j in range(M):
      if lawn[i][j] < rs[i] and lawn[i][j] < cs[j]:
        res = "NO"
        break
    if res == "NO":
      break
  fout.write("Case #"+str(t+1)+": "+res+"\n")