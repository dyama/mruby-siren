#!/usr/bin/siren
# coding: utf-8

def brep2js(shape, path)
  File.open(path, "w") do |f|
    f.write "var fs = [];\n"
    f.write "var es = [];\n"
    if shape.explore(ShapeType::FACE).size > 0
      i = 0
      f.write "{\n"
      f.write "  var g = new THREE.Geometry();\n"
      shape.explore(ShapeType::FACE) do |face|
        face.triangle(1.0e-1, 1.0e-1).each do |m|
          f.write "  g.vertices.push(new THREE.Vector3(#{m[0][0]}, #{m[0][1]}, #{m[0][2]}));\n"
          f.write "  g.vertices.push(new THREE.Vector3(#{m[1][0]}, #{m[1][1]}, #{m[1][2]}));\n"
          f.write "  g.vertices.push(new THREE.Vector3(#{m[2][0]}, #{m[2][1]}, #{m[2][2]}));\n"
          f.write "  var face#{i} = new THREE.Face3(#{i}, #{i+1}, #{i+2});\n"
          f.write "  face#{i}.normal = new THREE.Vector3(#{m[5][0]}, #{m[5][1]}, #{m[5][2]});\n"
          f.write "  g.faces.push(face#{i});\n"
          i += 3
        end
      end
      f.write "  fs.push(g);\n"
      f.write "}\n";
    elsif shape.explore(ShapeType::EDGE, ShapeType::FACE).size > 0
      shape.explore(ShapeType::EDGE, ShapeType::FACE) do |edge|
        i = 0
        f.write "{\n"
        f.write "  var g = new THREE.Geometry();\n"
        edge.to_pts(1.0e-6).each do |pts|
          pts.each do |pt|
            f.write "  g.vertices.push(new THREE.Vector3(#{pt.x}, #{pt.y}, #{pt.z}));\n" 
          end
        end
        f.write "  es.push(g);\n"
        f.write "}\n";
      end
    end
  end
end

model = nil
if ARGV.size == 0
  box = Prim::box [10, 10, 10], [5, 5, 5]
  foo = Prim::cylinder [], Vec::zdir, 15, 10, Math::PI * 3.0 / 2.0
  model = foo.fuse box
else
  model = BRepIO::read ARGV[0]
end

brep2js model, "model.js"

