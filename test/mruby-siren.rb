#!mruby

puts "--------------"
puts "mruby-siren.rb"
puts "--------------"

sp = Vec.new(5.0, 1.2, 3.8)
tp = Vec.new(8.0, 4.2, 3.8)

a = Build.line(sp, tp)
BRepIO.save(a, "./hoge.brep")

b = BRepIO.load("./hoge.brep");
p b.shapetype

