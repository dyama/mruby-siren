#
# AutoCAD DXF file I/O method
#
module Siren

  def self.save_dxf(shape, path, deflect = 1.0, angle = 5.0.to_rad)
    File.open(path, "w") do |f|
      @ff = f
      def w(code, data)
        @ff.write "% 3d\n#{data}\n" % [code]
      end
      def wp(pt, ofs = 0)
        w 10 + ofs, pt.x
        w 20 + ofs, pt.y
        w 30 + ofs, pt.z
      end
      w 0, "SECTION"
      w 2, "ENTITIES"
      shape.vertices(Siren::Shape::EDGE).each do |e|
        w 0, "POINT"
        w 8, "0"
        wp e.xyz
      end
      shape.edges(Siren::Shape::FACE).each do |e|
        ps = e.to_pts(deflect)
        if ps.size == 2
          w 0, "LINE"
          w 8, "0"
          wp ps.first
          wp ps.last, 1
        else
          w 0, "POLYLINE"
          wp [0, 0, 0]
          w 8, "0"
          w 66, 1
          w 70, 8 # 3D=8,2D=0
          ps.each do |pt|
            w 0, "VERTEX"
            w 8, "0"
            wp pt
          end
          w 0, "SEQEND"
        end
      end
      shape.faces.each do |face|
        face.triangle(deflect, angle).each do |m|
          w 0, "3DFACE"
          w 8, "0"
          mm = m[0,3]
          wp mm[0]
          wp mm[1], 1
          wp mm[2], 2
          wp mm[0], 3
          w 70, 8
        end
      end
      w 0, "ENDSEC"
      w 0, "EOF"
    end
    nil
  end

  def save_dxf(*args)
    Siren.save_dxf(*args)
  end

end

