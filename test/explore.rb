
a = Prim.box Vec.new 10, 20, 30

a.explore(ShapeType::FACE) do |face, depth|
  puts ShapeType::to_s(face.shapetype)
  puts "depth: " + depth.to_s
end

