#!siren

puts "make prim"
box = Prim.box(Vec.new(10, 10, 10));

puts "loc1"
loc1 = box.loc

puts "translate"
box.translate!(Vec.new(5, 0, 0));
p box.bndbox

puts "loc2"
loc2 = box.loc

# puts "translate"
# box.translate!(Vec.new(-5, 0, 0));

puts "set loc"
box.loc = loc1
p box.bndbox

puts "loc3"
loc3 = box.loc

puts "make another prim"
box2 = Prim.box(Vec.new(10, 10, 10))
p box2.bndbox
puts "set box1's loc to box2"
box2.loc = loc2
p box2.bndbox

p loc1 == loc2 # => false
p loc1.equal? loc3 # => expected true but false!

