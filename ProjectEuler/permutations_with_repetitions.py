

class PermutationsWithRepetitions:
  def __init__(self,seq,k):
    self.k = k
    self.n = len(seq)
    self.seq = list(seq)
    self.perms = self.k*[0]
    
  def get(self):
    return [self.seq[p] for p in self.perms]
    
  def next(self):
    k = self.k
    n = self.n
    perms = self.perms
  
    res = True
  
    i = k-1
    while i >= 0 and perms[i]==n-1: i-=1
    
    if i == -1: res = False    
    else: 
      perms[i]+=1
      perms[i+1:]=(k-i-1)*[0]
      
    return res  
    
    
if __name__ == "__main__":
  p = PermutationsWithRepetitions(range(5),3)
  print p.get() 
  while p.next():
    print p.get()  
    
    
    
    
    