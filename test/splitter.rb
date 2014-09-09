#!siren

w, h = gets.chomp.split(/ *, */).collect{ |s| s.to_f }

plane = Build.plane(
  Vec.new(0, 0, 0),
  Vec.new(1, 0, 0),
  Vec.new(0, 1, 0),
  0, w, 0, h);

edges = []
while line = gets
  break if line == nil || line.chomp == ""
  next if line =~ /^ *#/
  sy, sz, ty, tz = line.chomp.split(/ *, */).collect{ |s| s.to_f }
  sp = Vec.new 0, sy, sz
  tp = Vec.new 0, ty, tz
  edges.push(Build.line sp, tp)
end
ecomp = Build.compound edges

p "split"

#E = Build.line(Vec.new(0, 0, h/2), Vec.new(0, w, h/2))
E = Build.polyline [
  Vec.new(0, 0, h/2),
  Vec.new(0, w/2, h/2),
  Vec.new(0, w/2, h),
]

p ShapeType::to_s(E.shapetype)
# pls = Feat.splitEF ecomp, plane
pls = Feat.splitEF E, plane

BRepIO.save pls, "hoge.brep"

