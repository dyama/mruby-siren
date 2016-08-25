#!siren
# coding: utf-8

def make_hulllines(hs)
  b = hs.bndbox
  # Make water line
  wls = []
  (0..b.max.z).each do |d|
    plane = Build.infplane [0, 0, d], Vec.zdir
    line = hs.section plane
    break if line.explore(ShapeType::EDGE).size == 0
    wls << line
  end
  # Make station line
  sls = []
  stps = [ -0.190, -0.095, 0.0, 0.25, 0.5, 0.75, 1.0,
    2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 7.0, 7.5, 8.0, 8.5, 9.0,
    9.25, 9.5, 9.75, 9.875, 10.0, 10.095]
  stps.each do |st|
    x = b.max.x * st / 10.0
    plane = Build.infplane [x, 0, 0], Vec.xdir
    line = hs.section plane
    break if line.explore(ShapeType::EDGE).size == 0
    sls << line
  end
  BRepIO.save Build.compound(wls + sls), "hull-lines.brep"
end

if !File.exist? "face.brep"
  puts "face.brep がありません。"
else
  hullsurf = BRepIO.load "face.brep"
  make_hulllines hullsurf
end

