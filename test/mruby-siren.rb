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

