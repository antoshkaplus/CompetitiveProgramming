
TODO:
* test cases for SPOJ/FAMILY
* LISTREE
* ONEXLIS
* LIS2
* PRJAN15E
* MTOTALF
* FASTFLOW
* sliding windows:
    KPMATRIX, MATRIX2

Best practices:
  use method with following signature
  to easy switch between online, offline input mode
    void solve(istream& cin, ostream& cout);


Problems to revise:
SPOJ/RHOMBS
  solution is very easy. but idea should be explained.
  there are probably some geometrical rules involved.
SPOJ/MATCHING
  Hopcroft-Karp should be learnt and put into Ant library.

# to solve:
    MxN plane 2D. height + elevation map. How much water can be trapped:
    M,N < 110, 0 < h < 20'000. 
    
    Sample:
    [1,4,3,1,3,2]
    [3,2,1,3,2,4] => 4
    [2,3,3,2,3,1]
  
* pick any element of the grid, if has lower height - go there
* if has of equal height
* if greater, we do union find algo here such set has height at which it spills, also current level 
