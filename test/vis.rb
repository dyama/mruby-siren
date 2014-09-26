#!ruby

display = `echo $DISPLAY`.chomp
puts "display : #{display}"

window = X11.test
puts "window : #{window}"

world = World.new display
cam = Camera.new world, window

skin1 = Skin.new Prim.sphere(15, Vec::origin)
skin1.color = ColorName::RED
skin1.material = MaterialName::STONE
#skin1.transparency = 0.5
world.add skin1

puts "color: #{skin1.color}"
puts "material: #{skin1.material}"
puts "transparency: #{skin1.transparency}"

def deg2rad(deg)
  pi = 3.141592
  pi / 180.0 * deg
end

box = Prim.box Vec.new(5, 5, 20), Vec.new(10, 0, 0)
box.rotate! Vec::origin, Vec::zdir, deg2rad(25)
skin2 = Skin.new box
skin2.color = ColorName::GREEN
skin2.material = MaterialName::SHINY_PLASTIC
world.add skin2

cam.fit

puts "Press enter key to exit."
STDIN.gets

