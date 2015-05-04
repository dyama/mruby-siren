#!ruby

display = `echo $DISPLAY`.chomp
puts "display : #{display}"

window = X11Window::new
puts "window : #{window}"

world = World::new display
cam = Camera::new world, window.handle

file = "/opt/opencascade-6.8.0/data/occ/Axis_of_bearing.brep"
if File.exist? file
  skin1 = Skin.new BRepIO.load file
else
  skin1 = Skin.new Prim.sphere 10
end

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

