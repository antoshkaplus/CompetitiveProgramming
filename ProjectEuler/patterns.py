

class Patterns:
  def __init__(self,n,k):
    self.seq = (n-k)*[0]+k*[1]
    self.n = n
    self.k = k
    
  def get(self):
    return self.seq
    
  def next(self):
    n = self.n
    seq = self.seq
    
    res = True
    
    i = n-1
    # while can't shift one 
    while i > 0 and not (seq[i]==1 and seq[i-1]==0): i-=1    
    
    # able to shift 
    if i != 0:
      seq[i-1] = 1 
      s = sum(seq[i:])-1
      seq[i:]=len(seq[i:])*[0]        
      seq[n-s:]=s*[1]
    else: res = False
    
    return res
    
    

if __name__ == "__main__":
  p = Patterns(4,2)
  print p.get()
  while p.next():
    print p.get()
  
        
        