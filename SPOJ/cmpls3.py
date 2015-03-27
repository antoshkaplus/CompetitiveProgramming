
"""
Complete the Sequence!

Problem code: CMPLS

You probably know those quizzes in Sunday magazines: given the sequence 1, 2, 3, 4, 5, what is the next number? 
Sometimes it is very easy to answer, sometimes it could be pretty hard. Because these "sequence problems" are very popular, 
ACM wants to implement them into the "Free Time" section of their new WAP portal.

ACM programmers have noticed that some of the quizzes can be solved by describing the sequence by polynomials. 
For example, the sequence 1, 2, 3, 4, 5 can be easily understood as a trivial polynomial. The next number is 6. 
But even more complex sequences, like 1, 2, 4, 7, 11, can be described by a polynomial. In this case, 1/2.n2-1/2.n+1 
can be used. Note that even if the members of the sequence are integers, polynomial coefficients may be any real numbers.

Polynomial is an expression in the following form: 
P(n) = a(D).n(D)+a(D-1).n(D-1)+...+a1.n+a0
If aD <> 0, the number D is called a degree of the polynomial. Note that constant function P(n) = C can be considered 
as polynomial of degree 0, and the zero function P(n) = 0 is usually defined to have degree -1.

Input
There is a single positive integer T on the first line of input (equal to about 5000). 
It stands for the number of test cases to follow. Each test case consists of two lines. 
First line of each test case contains two integer numbers S and C separated by a single space, 
1 <= S < 100, 1 <= C < 100, (S+C) <= 100. 
The first number, S, stands for the length of the given sequence, the second number, 
C is the amount of numbers you are to find to complete the sequence.

The second line of each test case contains S integer numbers X1, X2, ... XS separated by a space. 
These numbers form the given sequence. The sequence can always be described by a polynomial P(n) such
that for every i, Xi = P(i). Among these polynomials, we can find the polynomial Pmin with the lowest possible degree. 
This polynomial should be used for completing the sequence.

Output
For every test case, your program must print a single line containing C integer numbers, separated by a space. 
These numbers are the values completing the sequence according to the polynomial of the lowest possible degree. 
In other words, you are to print values Pmin(S+1), Pmin(S+2), .... Pmin(S+C).
It is guaranteed that the results Pmin(S+i) will be non-negative and will fit into the standard integer type.

Example
Sample Input:
4
6 3
1 2 3 4 5 6
8 2
1 2 4 7 11 16 22 29
10 2
1 1 1 1 1 1 1 1 1 2
1 10
3
Sample Output:
7 8 9
37 46
11 56
3 3 3 3 3 3 3 3 3 3

"""

import sys
sys.stdin = open('test_in.txt','r')

n_max = 100
# difference table for all test cases
ps, pc = n_max*[0], n_max*[0]  

t = int(raw_input())
for k in range(t):
  s, c = map(int,raw_input().split())
  ps[:s] = map(int,raw_input().split())
  
  #! fill-in difference table
  w, sum = s, 1
  while sum != 0 and w != 1:  
    w-=1; sum=0
    for j in range(w):
      ps[j] = ps[j+1]-ps[j]
      sum += abs(ps[j]) 
        
  # h - index of row with 0-s or where only one element; w - number of elements in this row   
  
  #! finding unknown elements of sequense
  
  # take h-th row and fill it with same row value 
  pc[:c] = c*[ps[w-1]]
  # go up
  for v in ps[w:s]:
    pc[0] += v
    for j in range(1,c):
      pc[j] += pc[j-1]
  
  print " ".join(map(str,pc[:c]))
  