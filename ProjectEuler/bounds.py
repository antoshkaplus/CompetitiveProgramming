

def lower_bound_index(seq,b,i_st=0,i_fin=None):
  """ finding index i in sequence such that
      (seq[i] <= b) and (seq[i+1] > b if exists) """
  if i_fin == None: 
    i_fin = len(seq) - (1 if len(seq) else 0)
  
  found = True
  # if impossible to perform operation
  if seq == [] or seq[i_st] > b: found = False 
  else:
    # if bound at the end of seq
    if seq[i_fin] == b: i_st = i_fin 
    # else finding the bound
    else:
      while i_fin-i_st > 1:
        i = (i_fin+i_st)//2
        if seq[i] > b:
          i_fin = i
        else:
          i_st = i    
  return i_st,found
      
      
def upper_bound_index(seq,b,i_st=0,i_fin=None):
  """ finding index i in sequence such that
      (seq[i] >= b) and (seq[i-1] < b if exists) """
  if i_fin == None: 
    i_fin = len(seq) - (1 if len(seq) else 0)    
     
  found = True
  if seq == [] or seq[i_fin] < b: found = False
  else:
    if seq[i_st] == b: i_fin = i_st
    else:
      while i_fin-i_st > 1:
        i = (i_fin+i_st)//2
        if seq[i] < b:
          i_st = i
        else:
          i_fin = i      
  return i_fin,found


if __name__ == "__main__":
  seq = [4]
  print seq
  k = upper_bound_index(seq,5,0,len(seq)-1)
