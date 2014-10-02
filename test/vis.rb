#!ruby

display = `echo $DISPLAY`.chomp
puts "display : #{display}"

window = X11.test
puts "window : #{window}"

world = World.new display
cam = Camera.new world, window

skin1 = Skin.new BRepIO.load("/opt/occ671_work/data/occ/Axis_of_bearing.brep")
# model = BRepIO.load("/home/dyama/jobs/2014-10-01/output4.brep")
# model.scale! Vec.new(0, 0, 0), 0.001
# skin1 = Skin.new model
#skin1 = Skin.new Prim.sphere(5, Vec.new(-15, 0, 0))
skin1.color = ColorName::WHITE
skin1.material = MaterialName::DEFAULT
#skin1.transparency = 0.5
world.add skin1

puts "color: #{skin1.color}"
puts "material: #{skin1.material}"
puts "transparency: #{skin1.transparency}"

cam.fitz
cam.fit

puts "Press enter key to exit."
STDIN.gets

