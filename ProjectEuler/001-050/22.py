"""
Using 22.txt (right click and 'Save Link/Target As...'), 
a 46K text file containing over five-thousand first names, 
begin by sorting it into alphabetical order. Then working out 
the alphabetical value for each name, multiply this value by 
its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, 
COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. 
So, COLIN would obtain a score of 938 * 53 = 49714.

What is the total of all the name scores in the file?
"""

f = open("22.txt","r")
str = f.read()
f.close()

words = (str.replace("\"","")).split(",")

# max length of word
max_len = max(map(len,words))

table = len(words)*[0]
for i,w in enumerate(words):
  table[i] = map(lambda x:ord(x)-ord('A')+1,w) + (max_len-len(w))*[0]
  
# sequense number
seq_numb = 0

# begin with lower order
for i in range(max_len-1,-1,-1):
  # 26 - number of letters in alphabet + 0 if no letter on this position 
  lists = [[] for q in range(27)] 
  for t in table:
    lists[t[i]].append(t)
  
  table = []
  for l in lists:
    table.extend(l)
  

total_score = 0  
for i,t in enumerate(table):
  total_score += sum(t)*(i+1)
  
print total_score




