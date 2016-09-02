#
# STL file I/O method
#

module Siren

  def self.save_stl(shape, path, ascii = true, deflect = 1.0, angle = 5.0.to_rad)
    File.open(path, "w") do |f|
      if ascii
        f.write "solid shape, STL ascii file built with siren. http://siren.xyz/\n"
        shape.faces.each do |face|
          face.triangle(deflect, angle).each do |mesh|
            f.write "facet normal %8e %8e %8e\n" % mesh[5]
            f.write "  outer loop\n"
            f.write "    vertex %8e %8e %8e\n" % mesh[0]
            f.write "    vertex %8e %8e %8e\n" % mesh[1]
            f.write "    vertex %8e %8e %8e\n" % mesh[2]
            f.write "  endloop\n"
            f.write "endfacet\n"
          end
        end
        f.write "endsolid shape\n"
      else
        raise NotImplementedError
      end
    end
    nil
  end

  def save_stl(*args)
    Siren.save_stl *args
  end

end

