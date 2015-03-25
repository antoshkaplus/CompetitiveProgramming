
"""

Problem code: ONP

Transform the algebraic expression with brackets into RPN form (Reverse Polish Notation). 
Two-argument operators: +, -, *, /, ^ (priority from the lowest to the highest), brackets ( ). 
Operands: only letters: a,b,...,z. 
Assume that there is only one RPN form (no expressions like a*b*c).

Input

t [the number of expressions <= 100]
expression [length <= 400]
[other expressions]
Text grouped in [ ] does not appear in the input file.

Output

The expressions in RPN form, one per line.
Example

Input:
3
(a+(b*c))
((a+b)*(z+x))
((a+t)*((b+(a+c))^(c+d)))

Output:
abc*+
ab+zx+*
at+bac++cd+^*

"""

signs = '+-*/^'

result = ''

n = int(raw_input())
for i in range(n) :
  string = raw_input()
  stack = []
  for x in string :
    if   x == '(' : pass
    elif x == ')' : result += stack.pop()
    elif x in signs : stack.append(x)
    else : result += x
    
  result += '\n'  
    
print result    
    