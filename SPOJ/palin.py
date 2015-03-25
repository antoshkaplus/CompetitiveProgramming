

# one digit problem

import sys
sys.stdin = open('test_in.txt','r')
#sys.stdout = open('test_out.txt','w')

def is_nine(letter) :
  return letter == '9'   
 
def inc(part) :
  result = None
  part_len = len(part)
  for i in xrange(part_len-1,-1,-1) : 
    if is_nine(part[i]) :
      part[i] = '0'  
      if i == 0 :
        result = 1
        break        
    else :
      part[i] = chr(ord(part[i])+1) 
      break
  return result
  
n_tests = int(raw_input())
for n in range(n_tests) :
  numb = list(raw_input())
  numb_len = len(numb)
  numb_len_odd = numb_len % 2
  
  numb_len_half = numb_len/2

  done = False
  if numb_len >= 1 :
    part_1_pos = numb_len_half-1
    part_2_pos = numb_len_half-1+(2 if numb_len_odd else 1)
    for i in range(numb_len_half) :
      if numb[part_1_pos-i] != numb[part_2_pos+i] :
        if numb[part_1_pos-i] > numb[part_2_pos+i] :
          numb[part_2_pos+i:] = numb[part_1_pos-i::-1]
          done = True
        break
    
  if not done :  
    pass
    # take part_1 of numb
    part_numb = numb[:numb_len_half+(1 if numb_len_odd else 0)]
    if inc(part_numb) : numb = ['1'] + ['0']*(numb_len-1) + ['1'] 
    else : numb = part_numb[:] + part_numb[numb_len_half-1 if numb_len_odd else None::-1]
  
  print ''.join(numb) 
    
    