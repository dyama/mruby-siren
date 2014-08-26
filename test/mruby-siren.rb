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

BRepIO.save(cmp, "/tmp/hoge.brep")

cmp2 = BRepIO.load("/tmp/hoge.brep");
p cmp2.shapetype

ex = Exp.new cmp2, ShapeType::EDGE

if false
  while ex.more
    s = ex.current
    p "depth:" + ex.depth.to_s + " type:" + ShapeType::to_s(s.shapetype)
    ex.next()
  end
else
  ex.to_a.each do |s|
    p "type:" + ShapeType::to_s(s.shapetype)
  end
end

p "------------"
a = Build.vertex(3, 4, 5);
p a.location.to_a

