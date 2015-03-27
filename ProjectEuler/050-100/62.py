"""
The cube, 41063625 (3453), can be permuted to produce two other cubes: 
56623104 (3843) and 66430125 (4053). In fact, 41063625 is the smallest cube 
which has exactly three permutations of its digits which are also cube.

Find the smallest cube for which exactly five permutations of its digits are cube.
"""

import sys

b = 1
i = 1

while True:
  cubes = []
   
  b *= 10 
  el = i**3
  while el < b: 
    cubes.append(el)  
    i+=1
    el = i**3
  
  cubes = map(str,cubes)
  cubes_dict = {}
  for c in cubes:
    cs = "".join(sorted(c))
    if cs in cubes_dict: cubes_dict[cs].append(c)
    else: cubes_dict[cs] = [c]
  
  flag = False  
  for c_seq in cubes_dict.values():
    if len(c_seq) == 5: 
      print c_seq
      flag = True
    
  if flag: break
    
    