b = 27.0 / 2;
d = 14.0;

hold = Build.polygon [
  Vec.new(0, 0, 0),
  Vec.new(0, b, 0),
  Vec.new(0, b, d),
  Vec.new(0, 0, d),
]
puts ShapeType::to_s(hold.shapetype)

tst = Build.polyline [
  Vec.new(0, b/2, d),
  Vec.new(0, b/2, d * 0.9),
  Vec.new(0, b, d * 0.7),
]
puts ShapeType::to_s(tst.shapetype)

faces = Feat.splitEF tst, hold
puts ShapeType::to_s(faces.shapetype)

BRepIO.save faces, "/tmp/faces.brep"

