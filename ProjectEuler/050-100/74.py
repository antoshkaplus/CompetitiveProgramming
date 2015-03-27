
import operator as op

fact = [reduce(op.mul,range(1,i+1),1) for i in range(10)]
f = lambda a: sum(fact[i] for i in map(int,str(a)))  

n = 10**6

arr = n*[None]
arr[169] = 3
arr[363601] = 3
arr[1454] = 3
arr[871] = 2
arr[45361] = 2
arr[872] = 2


for i in range(1,10**6):
  if arr[i] == None:
    seq = [i]
    k = 0
    while True:
      a = f(seq[-1])
      if a == seq[-1]: 
        break
      if a < n and arr[a] != None:
        k = arr[a]
        break
      seq.append(a)
    k_seq = len(seq)
    for i1,s in enumerate(seq):
      if s < n: arr[s] = k+k_seq-i1
          
print len([a for a in arr if a == 60])