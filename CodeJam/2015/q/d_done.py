
def richard_wins(X, R, C):
  S = min(R, C)
  L = max(R, C)
  if (S * L) % X != 0: return True
  if X == 3 and S == 1: return True
  if X == 4 and S <= 2: return True
  if X == 5 and (S <= 2 or (S, L) == (3, 5)): return True
  if X == 6 and S <= 3: return True
  if X >= 7: return True
  return False

for tc in range(input()):
  X, R, C = map(int, raw_input().split())
  print "Case #%d: %s" % (tc + 1,
    "RICHARD" if richard_wins(X, R, C) else "GABRIEL")