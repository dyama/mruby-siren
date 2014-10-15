#!siren

puts "make prim"
box = Prim.box(Vec.new(10, 10, 10));

puts "loc1"
loc1 = box.loc

puts "translate"
box.translate!(Vec.new(5, 0, 0));

puts "loc2"
loc2 = box.loc

p loc1 == loc2 # => false

