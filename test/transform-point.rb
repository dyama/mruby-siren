
t = Trans::new
t.translation! [5, 0, 0]
t.rotation! Vec::zero, Vec::zdir, 15.0.to_rad

p [10, 0, 0].trans(t)

