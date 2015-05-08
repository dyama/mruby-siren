#!mruby

puts "--------------"
puts "mruby-siren.rb"
puts "--------------"

sp = [5.0, 1.2, 3.8]
tp = [8.0, 4.2, 3.8]
a = Build.line sp, tp

b = Build.vertex(1, 2, 3)

pts = []
pts.push [1, 2, 3]
pts.push [3, 3, 3]
pts.push [2, 1, 3]

c = Build.polyline pts

cmp = Build.compound [a, b, c]

cmp2 = nil
if true
  BRepIO.save(cmp, "/tmp/hoge.brep")
  cmp2 = BRepIO.load("/tmp/hoge.brep");
else
  IGES.save([cmp], "/tmp/hoge.iges")
  cmp2 = IGES.load("/tmp/hoge.iges", true);
end
p cmp2.shapetype

cmp2.explore ShapeType::EDGE do |edge, depth|
  p "depth:" + depth.to_s + " type:" + edge.shapetype.to_sname
end

