

import sys

check_file, correct_file = sys.argv[1:]
with open(check_file) as file1, open(correct_file) as file2:
  for i, (str1, str2) in enumerate(zip(file1,file2)):
    if str1 != str2:
      print "error at line %d" % i+1
      break
  else:
    print "check file is correct"