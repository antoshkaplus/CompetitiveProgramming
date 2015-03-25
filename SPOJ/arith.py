"""
Problem code: ARITH

One part of the new WAP portal is also a calculator computing expressions with very long numbers. 
To make the output look better, the result is formated the same way as is it usually used with manual calculations.

Your task is to write the core part of this calculator. Given two numbers and the requested operation, 
you are to compute the result and print it in the form specified below. 
With addition and subtraction, the numbers are written below each other. 
Multiplication is a little bit more complex: first of all, we make a partial result for every digit of one of the numbers, 
and then sum the results together.

Input
There is a single positive integer T on the first line of input (equal to about 1000). 
It stands for the number of expressions to follow. 
Each expression consists of a single line containing a positive integer number, an operator (one of +, - and *) 
and the second positive integer number. Every number has at most 500 digits. There are no spaces on the line. 
If the operation is subtraction, the second number is always lower than the first one. No number will begin with zero.

Output
For each expression, print two lines with two given numbers, the second number below the first one, last digits 
(representing unities) must be aligned in the same column. 
Put the operator right in front of the first digit of the second number. 
After the second number, there must be a horizontal line made of dashes (-).

For each addition or subtraction, put the result right below the horizontal line, 
with last digit aligned to the last digit of both operands.

For each multiplication, multiply the first number by each digit of the second number. 
Put the partial results one below the other, starting with the product of the last digit of the second number. 
Each partial result should be aligned with the corresponding digit. 
That means the last digit of the partial product must be in the same column as the digit of the second number. 
No product may begin with any additional zeros. 
If a particular digit is zero, the product has exactly one digit -- zero. 
If the second number has more than one digit, print another horizontal line under the partial results, 
and then print the sum of them.

There must be minimal number of spaces on the beginning of lines, with respect to other constraints. 
The horizontal line is always as long as necessary to reach the left and right end of both numbers 
(and operators) directly below and above it. 
That means it begins in the same column where the leftmost digit or operator of that two lines 
(one below and one above) is. It ends in the column where is the rightmost digit of that two numbers. 
The line can be neither longer nor shorter than specified.

Print one blank line after each test case, including the last one.

Example

Sample Input:

4
12345+67890
324-111
325*4405
1234*4

Sample Output:

 12345
+67890
------
 80235

 324
-111
----
 213

    325
  *4405
  -----
   1625
     0
 1300
1300
-------
1431625

1234
  *4
----
4936

"""

n_tests = int(raw_input())
for i in range(n_tests) :
  expression = raw_input()
  for x in ['+','-','*'] : 
    ind = expression.find(x)
    if ind != -1 :
      oper_1 = expression[:ind]
      oper_2 = expression[ind+1:]
      
      #start realize operations
      res = str({
        '+' : lambda x_1, x_2 : x_1 + x_2, 
        '-' : lambda x_1, x_2 : x_1 - x_2,
        '*' : lambda x_1, x_2 : x_1 * x_2     
      }[x](int(oper_1),int(oper_2)))
      res_len = len(res)
      
      # don't forget !!!
      oper_2 = x + oper_2
      
      oper_1_len = len(oper_1)
      oper_2_len = len(oper_2)
      
      if x == '-' or x == '+' or oper_2_len == 2 :
        dashes_len = max(oper_2_len,res_len)
        dashes = '-'*dashes_len
        
        max_len = max(oper_1_len,oper_2_len,res_len)
        result = '\n'.join([' '*(max_len-oper_1_len)+oper_1, 
                            ' '*(max_len-oper_2_len)+oper_2, 
                            ' '*(max_len-dashes_len)+dashes, 
                            ' '*(max_len-res_len)+res])  
      else :
        oper_1_numb = int(oper_1)
        # do loop without oper_2[0] (there is sign)
        solution = []
        for i, x in enumerate(oper_2[:0:-1]) : 
          solution.append(str(oper_1_numb*int(x)) + ' '*i)
        beg_dashes = '-'*max(oper_2_len,len(solution[0]))
        end_dashes = '-'*res_len
        solution = [oper_1,oper_2,beg_dashes] + solution + [end_dashes,res]
        
        max_len = res_len
        result = '\n'.join([' '*(max_len-len(x)) + x for x in solution])
        
      break
      
  print result + '\n'





