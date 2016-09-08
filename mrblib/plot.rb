#
# Gnuplot data file I/O method
#
module Siren

  def save_plot(shape, path, face_mode = false, deflect = 1.0, angle = 5.0.to_rad)
    File.open(path, "w") do |f|
      f.puts "# Created by siren - http://siren.xyz/"
      if face_mode
        shape.faces.map {|e|
          e.triangle(deflect, angle).map {|m|
            m[0,3]
          }
        }.flatten(1).each do |m|
          f.puts "%.f %.f %.f" % m[0]
          f.puts "%.f %.f %.f" % m[1]
          f.puts "%.f %.f %.f" % m[2]
          f.puts ""
        end
      else
        # Curve mode
        shape.edges.each do |e|
          e.to_pts(deflect).each do |pos|
            f.puts "%.f %.f %.f" % pos
          end
          f.puts ""
        end
      end
    end
    nil
  end

  def save_plot(*args)
    Siren.save_plot(*args)
  end

end

