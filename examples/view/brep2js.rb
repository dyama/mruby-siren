#!/usr/bin/siren
# coding: utf-8

def brep2js(shape, path, face_defl=1.0, face_angle=5.0.to_rad, edge_defl=5.0.to_rad)
  File.open(path, "w") do |f|
    f.write "var fs = [];\n"
    f.write "var es = [];\n"
    if shape.faces.size > 0
      i = 0
      f.write "{\n"
      f.write "  var g = new THREE.Geometry();\n"
      shape.faces do |face|
        face.triangle(face_defl, face_angle).each do |m|
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
        edge.to_pts(edge_defl).each do |pt|
          f.write "  g.vertices.push(new THREE.Vector3(#{pt.x}, #{pt.y}, #{pt.z}));\n" 
        end
        f.write "  es.push(g);\n"
        f.write "}\n";
      end
    end
  end
end

model = nil
if ARGV.size == 0
  puts "There is no specified file."
else
  model = BRepIO.load ARGV[0]
end

brep2js model, File.expand_path(File.dirname(__FILE__)) + "/model.js"
