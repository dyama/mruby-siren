#
# Stanford PLY file I/O method
#
module Siren

  def self.save_ply(shape, path, deflect = 1.0, angle = 5.0.to_rad)
    File.open(path, "w") do |f|
      fs = shape.faces.map {|e|
        e.triangle(deflect, angle).map {|m|
          m[0,3]
        }
      }.flatten(1)
      es = shape.edges(Siren::Face).map{|e|
        e.to_pts(deflect)
      }
      vs = [fs, es].flatten(2).sort.uniq
      f.puts "ply"
      f.puts "format ascii 1.0"
      f.puts "comment Created by siren - http://siren.xyz/"
      if vs.size > 0
        f.puts "element vertex %d" % vs.size
        f.puts "property float x"
        f.puts "property float y"
        f.puts "property float z"
      end
      if es.size > 0
        f.puts "element edge %d" % es.size
        f.puts "property uint vertex1"
        f.puts "property uint vertex2"
      end
      if fs.size > 0
        f.puts "element face %d" % fs.size
        f.puts "property list uchar uint vertex_indices"
      end
      f.puts "end_header"
      vs.each do |e|
        f.puts "%.f %.f %.f" % e
      end
      es.each do |e|
        sp = vs.index(e.first)
        tp = vs.index(e.last)
        f.puts "%d %d" % [sp, tp]
      end
      fs.each do |e|
        pts = e.map{|m| vs.index(m)}
        f.puts pts.size.to_s + " " + pts.join(" ")
      end
      nil
    end
  end

  def save_ply(*args)
    Siren.save_ply(*args)
  end

end

