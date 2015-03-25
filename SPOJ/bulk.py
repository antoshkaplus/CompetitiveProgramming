"""
Problem code: BULK

ACM uses a new special technology of building its transceiver stations. 
This technology is called Modular Cuboid Architecture (MCA) and is covered by a patent of Lego company. 
All parts of the transceiver are shipped in unit blocks that have the form of cubes of exactly the same size. 
The cubes can be then connected to each other. 
The MCA is modular architecture, that means we can select preferred transceiver configuration 
and buy only those components we need .

The cubes must be always connected "face-to-face", i.e. the whole side of one cube is connected to the whole side 
of another cube. One cube can be thus connected to at most six other units. The resulting equipment, 
consisting of unit cubes is called The Bulk in the communication technology slang.

Sometimes, an old and unneeded bulk is condemned, put into a storage place, and replaced with a new one. 
It was recently found that ACM has many of such old bulks that just occupy space and are no longer needed. 
The director has decided that all such bulks must be disassembled to single pieces to save some space. 
Unfortunately, there is no documentation for the old bulks and nobody knows the exact number of pieces 
that form them. You are to write a computer program that takes the bulk description and computes the number of unit cubes.

Each bulk is described by its faces (sides). A special X-ray based machine was constructed that is able to localise 
all faces of the bulk in the space, even the inner faces, because the bulk can be partially hollow 
(it can contain empty spaces inside). But any bulk must be connected (i.e. it cannot drop into two pieces) 
and composed of whole unit cubes.


Input
There is a single positive integer T on the first line of input (equal to about 1000). 
It stands for the number of bulks to follow. Each bulk description begins with a line containing single positive integer F, 
6 <= F <= 250, stating the number of faces. Then there are F lines, each containing one face description. 
All faces of the bulk are always listed, in any order. 
Any face may be divided into several distinct parts and described like if it was more faces. 
Faces do not overlap. Every face has one inner side and one outer side. No side can be "partially inner and partially outer".

Each face is described on a single line. The line begins with an integer number P stating the number of points that 
determine the face, 4 <= P <= 200. Then there are 3 x P numbers, coordinates of the points. 
Each point is described by three coordinates X,Y,Z (0 <= X,Y,Z <= 1000) separated by spaces. 
The points are separated from each other and from the number P by two space characters. 
These additional spaces were added to make the input more human readable. 
The face can be constructed by connecting the points in the specified order, 
plus connecting the last point with the first one.

The face is always composed of "unit squares", that means every edge runs either in X, Y or Z-axis direction. 
If we take any two neighbouring points X1,Y1,Z1 and X2,Y2,Z2, then the points will always differ in exactly one 
of the three coordinates. I.e. it is either X1 <> X2, or Y1 <> Y2, or Z1 <> Z2, other two coordinates are the same. 
Every face lies in an orthogonal plane, i.e. exactly one coordinate is always the same for all points of the face. 
The face outline will never touch nor cross itself.


Output
Your program must print a single line for every test case. 
The line must contain the sentence The bulk is composed of V units., where V is the volume of the bulk.

Example

Sample Input:

2
12
4  10 10 10  10 10 20  10 20 20  10 20 10
4  20 10 10  20 10 20  20 20 20  20 20 10
4  10 10 10  10 10 20  20 10 20  20 10 10
4  10 20 10  10 20 20  20 20 20  20 20 10
4  10 10 10  10 20 10  20 20 10  20 10 10
5  10 10 20  10 20 20  20 20 20  20 15 20  20 10 20
4  14 14 14  14 14 16  14 16 16  14 16 14
4  16 14 14  16 14 16  16 16 16  16 16 14
4  14 14 14  14 14 16  16 14 16  16 14 14
4  14 16 14  14 16 16  16 16 16  16 16 14
4  14 14 14  14 16 14  16 16 14  16 14 14
4  14 14 16  14 16 16  16 16 16  16 14 16
12
4  20 20 30  20 30 30  30 30 30  30 20 30
4  10 10 10  10 40 10  40 40 10  40 10 10
6  10 10 20  20 10 20  20 30 20  30 30 20  30 40 20  10 40 20
6  20 10 20  20 20 20  30 20 20  30 40 20  40 40 20  40 10 20
4  10 10 10  40 10 10  40 10 20  10 10 20
4  10 40 10  40 40 10  40 40 20  10 40 20
4  20 20 20  30 20 20  30 20 30  20 20 30
4  20 30 20  30 30 20  30 30 30  20 30 30
4  10 10 10  10 40 10  10 40 20  10 10 20
4  40 10 10  40 40 10  40 40 20  40 10 20
4  20 20 20  20 30 20  20 30 30  20 20 30
4  30 20 20  30 30 20  30 30 30  30 20 30

Sample Output:

The bulk is composed of 992 units.
The bulk is composed of 10000 units.
"""

import sys
sys.stdin = open("direct.in.txt","r")

class Face:
  __h = 0
  __points = []
  
  def __init__(self,h,points):
    self.__h =  h
    self.__points = points[:]
  
  def height(self): return self.__h
  
  def points(self): return self.__points[:]
  
  def point(self,i): return self.__points[i]
  
  def point_min(self):
    result = self.__points[0]
    for point in self.__points[1:]:
	  if point[0] < result[0] or (point[0] == result[0] and point[1] < result[1]):
	    result = point
    return result
	
  def get_segments(self):
    points = self.__points
    result = []
    prev = points[__h-1]
    for cur in points:
	  result.append(tuple(prev,cur))
	  prev = cur
    return result
  
  def write(self):
    print self.__h, " ",
    for p in self.__points:
      print p,
    print " "
   	  
# area of polynom
def area_of_polygon(points):
  result = 0
  prev = points[-1]
  for cur in points: 
    result += prev[0]*cur[1]-prev[1]*cur[0];
    prev = cur
  return abs(result/2)

  
# start algorithm  
t = int(raw_input())
for k in range(t):
  n = int(raw_input())
  faces = []
  
  # reading faces
  for i in range(n):
    face = map(int,raw_input().split())
    horizontal = True
	# take first 3-point coordinate and see are they the same
    h = face[3]
    for i in face[6::3]:
	  if h != i: horizontal = False; break
    if horizontal:
	  faces.append(Face(h,zip(face[1::3],face[2::3])))
  
  # sort faces
  faces.sort(key=Face.height)
  
  # main loop
  volume = 0
  prev_s = 0
  prev_h = 0
  for i, face in enumerate(faces):
   
    # finding minimal point
    point_min = face.point_min()
    print point_min
	
    face.f = 1
	# go by faces, that was before
    for face_before in faces[i-1::-1]:
      if face_before.height() < face.height():
        tot = 0                 
        prev = face_before.point(-1)
        for cur in face_before.points():
          if prev[0] == cur[0]:
            if prev[0] > point_min[0]:
              if (prev[1] > cur[1] and cur[1] <= point_min[1] < prev[1]) or \
                 (prev[1] < cur[1] and prev[1] <= point_min[1] < cur[1]):
 			    tot+=1				
          prev = cur
        if tot%2:
          face.f = -face_before.f;
          break;
       
    cur_h = face.height()
    volume += prev_s*(cur_h - prev_h);
    prev_s += face.f*area_of_polygon(face.points());
    prev_h = cur_h;
  
  print "The bulk is composed of %d units." % volume
	