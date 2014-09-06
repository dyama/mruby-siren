#!mruby

puts "--------------"
puts "mruby-siren.rb"
puts "--------------"

sp = Vec.new(5.0, 1.2, 3.8)
tp = Vec.new(8.0, 4.2, 3.8)
a = Build.line(sp, tp)

b = Build.vertex(1, 2, 3)

pts = []
pts.push Vec.new 1, 2, 3
pts.push Vec.new 3, 3, 3
pts.push Vec.new 2, 1, 3

c = Build.polyline pts

cmp = Build.compound([a, b, c])

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
  p "depth:" + depth.to_s + " type:" + ShapeType::to_s(edge.shapetype)
end

# p "------------"
# a = Build.vertex(3, 4, 5);
# p a.location.to_a
# 
# b = Prim.box [10, 10, 10]
# s = Prim.sphere 5

