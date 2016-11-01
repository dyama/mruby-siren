include Siren

xplane = infplane Vec.o, Vec.x
yplane = infplane Vec.o, Vec.y
zplane = infplane Vec.o, Vec.z

# zplane = plane Vec.o, Vec.z, Vec.y, -50, 50, -50, 50
# xplane = plane Vec.o, Vec.x, Vec.y, -50, 50, -50, 50

a = halfspace xplane, Vec.x
b = halfspace yplane, Vec.y
c = halfspace zplane, Vec.z

s = sphere
r1 = a.common s
r2 = b.common r1
r3 = c.common r2

save_brep r3, "/tmp/hoge.brep"

