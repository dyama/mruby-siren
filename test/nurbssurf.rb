#!siren
# coding: utf-8

def test1
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
  box = Prim.box Vec.new(5, 5, 5), Vec.new(2, 2, 1)
  es = Algo.section(surf, box)
  w = Build.wire es.explore(ShapeType::EDGE).map{|n|n}
  surf2 = Build.nurbssurf udeg, uknots, vdeg, vknots, poles, w

  if surf2 != nil && !surf2.null?
    BRepIO::save surf2, "/tmp/nurbssurf.brep"
    BRepIO::save box, "/tmp/box.brep"
  else
    puts "Failed to make NURBS surface."
  end
end

def test2
  udeg = 1
  uknots = [[0, 2], [1, 2]]
  vdeg = 1
  vknots = [[0, 2], [1, 2]]
  poles = [
    [[Vec::new(0,  0, 0), 1.0], [Vec::new(10,  0, 0), 1.0]],
    [[Vec::new(0, 10, 0), 1.0], [Vec::new(10, 10, 0), 1.0]],
    [[Vec::new(0, 20, 0), 1.0], [Vec::new(10, 20, 0), 1.0]]
  ]

  w = Build.polyline [
    Vec::new( 0,  0, 0),
    Vec::new( 0, 10, 0),
    Vec::new(10, 10, 0),
    Vec::new(10,  0, 0),
    Vec::new( 0,  0, 0),
  ]

  ww = w.translate(Vec::new(-5, -5, 0))
  surf = Build.nurbssurf udeg, uknots, vdeg, vknots, poles, ww

  if surf != nil && !surf.null?
    BRepIO::save surf, "/tmp/nurbssurf.brep"
    BRepIO::save ww, "/tmp/wire.brep"
    puts "Done"
  else
    puts "Failed to make NURBS surface."
  end
end

test2

