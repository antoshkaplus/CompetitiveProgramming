"""
The n-th term of the sequence of triangle numbers is given by, 
t{n} = 1/2*n(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to 
its alphabetical position and adding these values we form a word value. 
For example, the word value for SKY is 19 + 11 + 25 = 55 = t{10}. 
If the word value is a triangle number then we shall call the word a triangle word.

Using words.txt (right click and 'Save Link/Target As...'), 
a 16K text file containing nearly two-thousand common English words, how many are triangle words?
"""

from sets import Set 
  
f = open("words.txt","r")
str = f.read()

words = str[1:len(str)-1].split("\",\"")

bound = 20*26
trian_numbs = Set()
i = 1
while True: 
  trian = i*(i+1)/2
  if trian > bound: break
  trian_numbs.add(trian)
  i+=1
  
trian_words = 0  
for w in words: 
  if sum(map(lambda x:ord(x)-ord('A')+1,w)) in trian_numbs:
    trian_words += 1

print trian_words  
  


