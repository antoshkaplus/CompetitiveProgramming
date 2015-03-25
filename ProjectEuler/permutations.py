

class Permutations:
  def __init__(self,elems,k):
    seq = sorted(elems)
    self.seq = seq[:k]+seq[:k-1:-1]
    self.n = len(seq)
    self.k = k
        
  def get(self,rest=False):
    k = self.k
    seq = self.seq
    res = seq[:k] if not rest else (seq[:k],seq[k:])
    return res
    
  def next(self):
    k = self.k
    n = self.n
    seq = self.seq    
    
    res = True
    
    i = k-1
    while i != -1:
      j = n-1
      while j != i and seq[j] < seq[i]: j-=1

      if j != i:
        seq[i], seq[j] = seq[j], seq[i]
        if i != k-1:
          d = n-len(seq[i+1:k+1])-1
          seq[i+1:k+1], seq[:d:-1] = seq[:d:-1], seq[i+1:k+1]
          seq[k:] = seq[:k-1:-1]
        break 

      i-=1      
    
    if i == -1: res = False
    return res    
    
    
    
if __name__ == "__main__":
  k = 6
  n = 6
  p = Permutations(range(n),k)
  print p.get()
  while p.next():
    print p.get()
  