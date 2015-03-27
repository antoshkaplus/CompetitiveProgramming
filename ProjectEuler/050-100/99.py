
from math import log

couples = [map(int,s.split(",")) for s in open("base_exp.txt")]

p = max(couples,key=lambda x: x[1]*log(x[0]))
print couples.index(p)