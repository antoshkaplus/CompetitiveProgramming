

f = open("B-small-practice.in")
s = f.read().split("\n")
T = int(s[0])
for t in range(1,T+1):
  E, R, N = map(int, s[2*t-1].split())
  vs = map(int, s[2*t].split())
  if E < R: print "here" 
  es = N*[R]
  es[0] = E
  inds = range(N)
  inds.sort(key=lambda i: vs[i], reverse=True)
  for k in range(N-1):
    i = inds[k]
    j = i-1
    c = E-es[i]
    while j >= 0:
      if vs[i] > vs[j]:
        if c > es[j]:
          c -= es[j]
          es[j] = 0
        else:
          es[j] -= c
          c = 0
          break
      j -= 1
    es[i] = E-c
  res = sum(map(lambda x, y: x*y, es, vs))
  print "Case #"+str(t)+": "+str(res)

