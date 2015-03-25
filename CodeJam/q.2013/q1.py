
def empty(table):
  res = False
  for r in table:
    for c in r:
      if c == '.':
        res = True
  return res

def win(table, symbol):
  res = False
  flag3 = True
  flag4 = True
  for i in range(4):
    flag1 = True
    flag2 = True
    for j in range(4):
      if table[i][j] != symbol:
        flag1 = False
      if table[j][i] != symbol:
        flag2 = False
    if flag1 or flag2:
      res = True
      break
    if table[i][i] != symbol:
      flag3 = False
    if table[i][3-i] != symbol:
      flag4 = False
  if flag3 or flag4:
    res = True
  return res


def substituteT(table, symbol):
  t2 = 4*[None]
  for i, r in enumerate(table):
    t2[i] = list(r)
    for j in range(4):
      if r[j] == 'T':
        t2[i][j] = symbol
  return t2

fout = open("out.txt", "w")
f = open("test.txt", "r")
s = f.read().split("\n")
N = int(s[0])
for i in range(N):
  res = None
  i1 = 5*i + 1
  i2 = i1+4
  t = map(list, s[i1:i2])
  if win(substituteT(t, 'X'), 'X'):
    res = "X won"
  elif win(substituteT(t, 'O'), 'O'):
    res = "O won"
  elif empty(t):
    res = "Game has not completed"
  else:
    res = "Draw"
  fout.write("Case #"+str(i+1)+": "+res+"\n")



