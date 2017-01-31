#
# SVG file I/O method
#

module Siren

  def self.save_svg(shape, path, deflect = 1.0, angle = 5.0.to_rad)
    File.open(path, "w") do |f|
      df = 0.5 # Depth factor
      header = <<-EOF
<?xml version='1.0' encoding='utf-8'?>
<!-- This SVG file built with siren. http://siren.xyz/ -->
<svg xmlns='http://www.w3.org/2000/svg'>
  <defs>
    <style type='text/css'><![CDATA[
      path {
        fill: none;
        stroke: black;
        stroke-width: 1;
      }
    ]]></style>
  </defs>
  <g transform="matrix(1,0,0,1,0,0)">
      EOF
      f.write header
      shape.edges.each do |edge|
        pts = edge.to_pts(deflect)
        sp = pts.shift
        d = "M#{sp.y + sp.x * df},#{sp.z + sp.x * df}"
        pts.each {|pt| d << "L#{pt.y + pt.x * df},#{pt.z + pt.x * df}" }
        f.write "    <path d='#{d}' />\n"
      end
      f.write "  </g>\n"
      f.write "</svg>\n"
    end
    nil
  end

  def save_svg(*args)
    Siren.save_svg(*args)
  end

end

