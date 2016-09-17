# test file for face.cut

include Siren

small = 10e-4

# 3x3 plane to be cut
myface = plane [0, 0], Vec.z, Vec.x, 0, 3, 0, 3

# cylinders used for cut
mycylinder1 = cylinder [1,0,0], [0,1,0], small, 2, Math::PI*2
mycylinder2 = cylinder [1,1,0], [1,0,0], small, 2, Math::PI*2
mycylinder3 = cylinder [2,1,0], [0,1,0], small, 2, Math::PI*2
mycylinder4 = cylinder [0,2,0], [1,0,0], small, 2, Math::PI*2

comp = compound [mycylinder1,mycylinder2,mycylinder3,mycylinder4]

# apply cut iteratively
res = myface.cut mycylinder1
res = res.cut mycylinder2
res = res.cut mycylinder3
res = res.cut mycylinder4
save_stl res,"cut1.stl"

# the following does not work; compound should not have self-intersections.
# to avoid this, we have first to make the union (fuse) of the compound
res2 = myface.cut comp
save_stl res2,"cut2.stl"
