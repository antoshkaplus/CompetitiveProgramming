


class Combinations:
  def __init__(self,seq,k):
    self.n = len(seq)
    self.k = k
    self.seq = list(seq)
    self.combs = [0]*(self.n-k)+[1]*k
   
  def get(self):
    return [self.seq[i] for i,c in enumerate(self.combs) if c]
  
  def next(self):
    k = self.k
    n = self.n
    combs = self.combs
  
    res = True
	
    i = n-1
    while i > 0 and not (combs[i]==1 and combs[i-1]==0): i-=1
    
    if i == 0: res = False
    else:
      combs[i-1] = 1 
      s = sum(combs[i:])-1
      combs[i:]=len(combs[i:])*[0]        
      combs[n-s:]=s*[1]
     
    return res


	
if __name__ == "__main__":
  c = Combinations("anto",2)
  print c.get()
  while c.next():
    print c.get()







	