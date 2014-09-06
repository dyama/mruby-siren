
a = Prim.box Vec.new 10, 5, 3

bb = a.bndbox

puts "x"
p bb.min.x
p bb.max.x

puts "y"
p bb.min.y
p bb.max.y

puts "z"
p bb.min.z
p bb.max.z
