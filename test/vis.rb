#!ruby

display = `echo $DISPLAY`.chomp
puts "display : #{display}"

window = X11Window::new
puts "window : #{window}"

world = World::new display
cam = Camera::new world, window.handle

skin1 = Skin.new Prim.sphere 10

skin1.color = ColorName::RED
skin1.material = MaterialName::DEFAULT

world.add skin1

puts "color: #{skin1.color}"
puts "material: #{skin1.material}"
puts "transparency: #{skin1.transparency}"

cam.fitz
cam.fit

puts "Press enter key to exit."
STDIN.gets

