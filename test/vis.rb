#!ruby

display = `echo $DISPLAY`.chomp
puts "display : #{display}"

window = X11.test
puts "window : #{window}"

world = World.new display
cam = Camera.new world, window

skin = Skin.new Prim.sphere(20, Vec.new(10, 10, 10))

skin.color = ColorName::BLUE1
skin.material = MaterialName::STONE
skin.transparency = 0.5

world.add skin
cam.fit

if true
  while true
    Sleep::sleep 1
  end
else
  Sleep::sleep 3
  world.erase skin
  Sleep::sleep 3
end

