
path = "/tmp/test.igs"

def js_line(path)
  puts "var m = new THREE.LineBasicMaterial({color: 0xffffff});"
  puts "var g = null;"
  BRepIO.load(path).explore(ShapeType::EDGE) do |e|
    puts "g = new THREE.Geometry();"
    e.to_pts.each do |vs|
      vs.each do |v|
        puts "g.vertices.push(new THREE.Vector3(#{v.x/1000.0}, #{v.y/1000.0}, #{v.z/1000.0}));"
      end
    end
    puts "scene.add(new THREE.Line(g, m));"
  end
end

IGES.load(path).each do |shape|
  shape.explore(ShapeType::FACE) do |face|
    p face.triangle 1.0, 15.0
  end
end
