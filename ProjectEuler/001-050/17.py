"""
If the numbers 1 to 5 are written out in words: one, two, three, four, five, 
then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, 
how many letters would be used?

NOTE: Do not count spaces or hyphens. 
For example, 342 (three hundred and forty-two) contains 23 letters and 
115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing 
out numbers is in compliance with British usage.
"""

total = 0

ones = {0:0,1:len('one'),2:len('two'),3:len('three'),4:len('four'),5:len('five'),
        6:len('six'),7:len('seven'),8:len('eight'),9:len('nine')}

teens = {1:len('eleven'),2:len('twelve'),3:len('thirteen'),4:len('fourteen'),
         5:len('fifteen'),6:len('sixteen'),7:len('seventeen'),8:len('eighteen'),
         9:len('nineteen')}        
        
tens = {0:0,1:len('ten'),2:len('twenty'),3:len('thirty'),4:len('forty'),5:len('fifty'),
        6:len('sixty'),7:len('seventy'),8:len('eighty'),9:len('ninety')}

hundred = len('hundred')
        
bond = len('and')
        
for i in range(10): # hundreds
  for j in range(10): # tens
    for k in range(10): # ones
      if i != 0 : 
        total += ones[i]+hundred 
        if j != 0 or k != 0: total += bond 
      
      if j == 1 and k > 0: total += teens[k]
      else: total += tens[j]+ones[k] 
      
total += ones[1] + len('thousand')      
      
print total    

