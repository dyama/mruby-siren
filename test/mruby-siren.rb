#!mruby

puts "--------------"
puts "mruby-siren.rb"
puts "--------------"

sp = Vec.new(5.0, 1.2, 3.8)
tp = Vec.new(8.0, 4.2, 3.8)
a = Build.line(sp, tp)

b = Build.vertex(1, 2, 3)

c = Build.compound([a, b])

BRepIO.save(c, "/tmp/hoge.brep")

cc = BRepIO.load("/tmp/hoge.brep");
p cc.shapetype

