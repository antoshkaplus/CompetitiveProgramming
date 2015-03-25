"""
Each character on a computer is assigned a unique code and the preferred standard 
is ASCII (American Standard Code for Information Interchange). For example, 
uppercase A = 65, asterisk (*) = 42, and lowercase k = 107.

A modern encryption method is to take a text file, convert the bytes to ASCII, 
then XOR each byte with a given value, taken from a secret key. 
The advantage with the XOR function is that using the same encryption key on the cipher text, 
restores the plain text; for example, 65 XOR 42 = 107, then 107 XOR 42 = 65.

For unbreakable encryption, the key is the same length as the plain text message, 
and the key is made up of random bytes. The user would keep the encrypted message 
and the encryption key in different locations, and without both "halves", 
it is impossible to decrypt the message.

Unfortunately, this method is impractical for most users, so the modified method is 
to use a password as a key. If the password is shorter than the message, which is likely, 
the key is repeated cyclically throughout the message. The balance for this method is 
using a sufficiently long password key for security, but short enough to be memorable.

Your task has been made easy, as the encryption key consists of three lower case characters. 
Using cipher1.txt (right click and 'Save Link/Target As...'), a file containing the encrypted
ASCII codes, and the knowledge that the plain text must contain common English words, 
decrypt the message and find the sum of the ASCII values in the original text.
"""



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
    


f = open("cipher1.txt","r")
enc_codes = map(int,(f.read()).split(","))
f.close()

f = open("words.txt","r")
words = map(lambda x: x[1:-1].lower(),(f.read()).split(","))
f.close()

alph_list = "abcdefghijklmnopqrstuvwxyz"
alph_codes = map(ord,alph_list)

n_keys = 3
perms = PermutationsWithRepetitions(alph_codes,n_keys)

main_text = ""
main_value = 0
main_sum = 0


while True:
  key_samp = perms.get() 
  
  dec_codes = len(enc_codes)*[0]
  for i,k in enumerate(key_samp):
    dec_codes[i::n_keys] = map(lambda x: x^k,enc_codes[i::n_keys]) 
  dec_text = ("".join(map(chr,dec_codes))).lower() 
  if sum([dec_text.count(let) for let in alph_list+" "]) > 0.9*len(dec_text):
    dec_sum = sum(dec_codes)    
    dec_value = 0
    for w in words: 
      dec_value += (dec_text.count(w)*len(w)**2)
      
    if dec_value > main_value:
      main_value,main_sum,main_text = dec_value,dec_sum,dec_text
    
  if not perms.next(): break
  
print main_value,"\n",main_sum,"\n",main_text


