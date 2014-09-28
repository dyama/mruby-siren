#!ruby

display = `echo $DISPLAY`.chomp
puts "display : #{display}"

window = X11.test
puts "window : #{window}"

world = World.new display
cam = Camera.new world, window

skin1 = Skin.new BRepIO.load("/opt/occ671_work/data/occ/Axis_of_bearing.brep")
#skin1 = Skin.new Prim.sphere(5, Vec.new(-15, 0, 0))
skin1.color = ColorName::WHITE
#skin1.material = MaterialName::DEFAULT
#skin1.transparency = 0.5
world.add skin1

puts "color: #{skin1.color}"
puts "material: #{skin1.material}"
puts "transparency: #{skin1.transparency}"

cam.fit

puts "Press enter key to exit."
STDIN.gets

