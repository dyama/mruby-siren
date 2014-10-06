#!siren
# coding: utf-8

# Sample options from DRAW TEST HARNESS
# bsplinesurf s   1 2 0 2 1 2   2 3 0 3 1 1 2 3   0 0 0 1  10 0 5 1   0 10 2 1  10 10 3 1   0 20 10 1  10 20 20 1   0 30 0 1  10 30 0 1
#                 u n u u u u   v n v v v v v v   x y z w  x  y z w   x y  z w  x  y  z w   x y  z  w  x  y  z  w   x y  z w  x  y  z w
#                 d k k m k m   d k k m k m k m   POLES ...
# Sample options from siren old edition
# bssurf 1,[[0,2],[1,2]],2,[[0,3],[1,1],[2,3]],[[[0,0,0,1],[10,0,5,1]],[[0,10,2,1],[10,10,3,1]],[[0,20,10,1],[10,20,20,1]],[[0,30,0,1],[10,30,0,1]]]

udeg = 1
uknots = [[0, 2], [1, 2]]
vdeg = 2
vknots = [[0, 3], [1, 1], [2, 3]]

poles = [
  [[Vec::new(0,  0,  0), 1.0], [Vec::new(10,  0,  5), 1.0]],
  [[Vec::new(0, 10,  2), 1.0], [Vec::new(10, 10,  3), 1.0]],
  [[Vec::new(0, 20, 10), 1.0], [Vec::new(10, 20, 20), 1.0]],
  [[Vec::new(0, 30,  0), 1.0], [Vec::new(10, 30,  0), 1.0]]
]

surf = Build.nurbssurf udeg, uknots, vdeg, vknots, poles

if surf != nil && !surf.null?
  BRepIO::save surf, "/tmp/nurbssurf.brep"
else
  puts "Failed to make NURBS surface."
end


