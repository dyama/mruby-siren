#!siren

puts "make box"
box = Prim.box(Vec.new(10, 10, 10));

puts "move box"
box.translate!(Vec.new(5, 0, 0));

p box

p box.pos

p box.loc

# box.translate!(Vec.new(5, 0, 0));
# 
# loc2 = box.location
# p loc2
# 
# p loc1 == loc2 # => false

