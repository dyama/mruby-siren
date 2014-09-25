#!ruby

world = World.new "localhost:10.0"
cam = Camera.new world, X11.test

world.add(Skin.new(Prim.sphere(20, Vec.new(10, 10, 10))))
cam.fit

while true
  puts "sleep"
  Sleep::sleep 1
end

