

g = {}
for s in open("keylog.txt"):
  for i,c in enumerate(s):
    if c not in g: g[c] = []
    if i+1 < len(s) and s[i+1] not in g[c]: 
      g[c].append(s[i+1])

      
# finding all nodes with no incoming edges      
s = dict(zip(g.keys(),len(g)*[0]))
for arr in g.values():
  for a in arr:  s[a] += 1
  
S = []
for k,v in s.items():
  if v==0: S.append(k)

L = []
while S:
  k = S.pop()
  L.append(k)
  for c in g[k]:
    t = 0
    for v in g.values():
      if c in v: t += 1
    if t == 1:
      S.append(c)
  g[k] = []
  
print L

    
    
    
    