
"""
some problems if two players has flush and something else !!!!
"""

# cards = ["..","..",...]
def count_score(cards):
  """ High Card: Highest value card.         0
      One Pair: Two cards of the same value. 1
      Two Pairs: Two different pairs.        2
      Three of a Kind: Three cards of the same value. 3
      Straight: All cards are consecutive values.     4
      Flush: All cards of the same suit.              5
      Full House: Three of a kind and a pair.         6 
      Four of a Kind: Four cards of the same value.   7
      Straight Flush: All cards are consecutive values of same suit. 8
      Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.        9 
  """
  v = {"2":0,"3":1,"4":2,"5":3,"6":4,"7":5, \
            "8":6,"9":7,"T":8,"J":9,"Q":10,"K":11,"A":12}    
  s = {"H":0,"C":1,"S":2,"D":3}
  
  c = map(lambda x:(v[x[0]],s[x[1]]),cards)
  c.sort(cmp=lambda x,y: x[0]-y[0])
  
  r_val = 0
  r_seq = [p[0] for p in c[::-1]]
  
  
  v_tab = {1:[],2:[],3:[],4:[]}
  k = 1
  for i in range(4):
    if c[i+1][0]==c[i][0]: k+=1
    else:
      v_tab[k].append(c[i][0])
      k = 1
  v_tab[k].append(c[4][0])
  
  
  #print v_tab
  
  if len(v_tab[1])<5: # exists some same values
    if v_tab[4] != []: # Four of a Kind
      r_val,r_seq = 7,v_tab[4]+v_tab[1]
    elif v_tab[3] != []: # Full House or Three of a Kind
      if v_tab[2] != []: 
        r_val,r_seq = 6,v_tab[3]+v_tab[2]
      else: r_val,r_seq = 3,v_tab[3]+v_tab[1][::-1]
    else: # Two Pairs or Pair
      if len(v_tab[2])==2: r_val,r_seq = 2,v_tab[2][::-1]+v_tab[1]
      else: r_val,r_seq = 1,v_tab[2]+v_tab[1][::-1]
  else: # maybe Straight ?
    if [c[i+1][0]-c[i][0] for i in range(4)]==[1,1,1,1]:
      r_val,r_seq = 4,[c[-1][0]] 
  
  # looking for Flush
  if [c[i+1][1]-c[i][1] for i in range(4)]==[0,0,0,0]:
    if r_val==4:
      if c[0][0]==8: r_val,r_seq = 9,[] # Royal Flush
      else: r_val = 8 # Straight Flush
    elif r_val < 5: 
      print "here"
      r_val = 5 # Flush
    
  return r_val,r_seq
      
  
f = open("poker.txt","r")
str = f.read()

res = 0
for game in map(lambda x:x.split(" "),str.split("\n"))[:]:
  v1,s1 = count_score(game[:5])
  v2,s2 = count_score(game[5:])
  #print v1,v2,s1,s2
  if v1 >= v2:
    if v1 > v2: res+=1
    else:       
      for p1,p2 in zip(s1,s2): 
        if p1 > p2:
          res+=1
          break
        if p1 < p2:
          break    
  
  
print res  
  