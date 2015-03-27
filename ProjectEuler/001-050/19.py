"""
You are given the following information, but you may prefer to do some research for yourself.

1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.

A leap year occurs on any year evenly divisible by 4, 
but not on a century unless it is divisible by 400.
How many Sundays fell on the first of the month during 
the twentieth century (1 Jan 1901 to 31 Dec 2000)?
"""

from datetime import date
from datetime import timedelta

d0 = date(1901,1,1)
d1 = date(2000,12,31)

i=0
t = timedelta(days=1)
while d0 <= d1:
  if d0.weekday() == 6 and d0.day == 1: i+=1
  d0 = d0 + t
  
print i