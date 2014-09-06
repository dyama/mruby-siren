
# 1. Offset table csv to surface/solid model.
# 2. Calculation hydrostatics table with solid model.

ofsfile = "/tmp/TABLE.csv"
lpp = 22.4

no = ""
sl = []
t = Hash.new

puts "Parse offset table..."
File.open(ofsfile, "r") do |f|
  f.each do |ln|
    if ln == nil then next end
    r = ln.chomp.split(/ *, */)
    case r[0]
    # Get ship no.
    when "!OFFSET"
      no = r[1].gsub(/\"/, "")
    # Get station line definitions
    when "SB"
      sl = r[2..-1].map{ |f| f = f.to_f }
    # Get offset data
    when /^SF\d{3}$/
      w = r[1].to_f
      i = 0
      r[2..-1].map{ |f| f = f.to_f }.each do |n|
        if t[sl[i]] == nil then t[sl[i]] = Hash.new end
        if t[sl[i]][w] == nil then t[sl[i]][w] = Hash.new end
        t[sl[i]][w] = n
        i += 1
      end
    end
  end
end

puts "Make hullshape surface..."
ws = Array.new
t.each do |x, ln|
  x = x * lpp / 10
  pts = Array.new
  ln.each do |z, y|
    pts.push Vec.new(x, y, z)
  end
  ws.push Build.polyline(pts)
end
hullsurf = Offset.loft ws

ae_line = t.sort_by{|k,v|k}.first
fe_line = t.sort_by{|k,v|k}.last
zmin    = ae_line.last.sort_by{|k,v|k}.first.first
zmax    = ae_line.last.sort_by{|k,v|k}.last.first
xmin    = ae_line.first
xmax    = fe_line.first * lpp / 10

puts "Make XZ plane on center line..."
cl_plane = Build.polygon [
  Vec.new(xmin, 0, zmin), Vec.new(xmin, 0, zmax),
  Vec.new(xmax, 0, zmax), Vec.new(xmax, 0, zmin),
]

puts "Make XY plane on top..."
pts = Array.new
pts.push(Vec.new(xmin, 0, zmax))
t.each do |x, ln|
  pts.push(Vec.new((x * lpp / 10), ln.sort.last.last, zmax))
end
pts.push(Vec.new(xmax, 0, zmax))
top_plane = Build.polygon pts

# Make end plate
def makeend(line)
  zmin = line.last.sort_by{|k,v|k}.first.first
  zmax = line.last.sort_by{|k,v|k}.last.first
  xpos = line.first
  pls = Array.new
  pts = nil
  line.last.sort_by{|k,v|k}.each_cons(2) do |cur,nex|
    cz = cur.first; cy = cur.last
    nz = nex.first; ny = nex.last
    if pts == nil
      # In out of polygon
      if cz == zmin && cy > 0 # Already started at first
        pts = Array.new
        pts.push Vec.new xpos, 0, zmin
        pts.push Vec.new xpos, cy, cz
        next
      end
      if cy == 0 && ny > 0    # Start polygon
        pts = Array.new
        pts.push Vec.new xpos, cy, cz
        next
      end
    else
      # In polygon
      pts.push Vec.new xpos, cy, cz
      if cy == 0              # Break from polygon
        pls.push Build.polygon pts
        pts = nil
      end
    end
  end
  if pts != nil
    pts.push Vec.new xpos, 0, zmax
    pls.push Build.polygon pts
  end
  return pls
end

puts "Make transom and F.E. plane..."
pl_transom = makeend ae_line
pl_foreend = makeend fe_line

comp = Build.compound [hullsurf, cl_plane, top_plane] + pl_transom + pl_foreend
BRepIO.save comp, "/tmp/#{no}.brep"

ex = Exp.new comp, ShapeType::FACE
while ex.more
  next if ex.current.null?
  p ("  " * ex.depth) + ex.current.to_s
  ex.next
end

#puts "Sewing faces to shell..."
#shell = Build.sewing [hullsurf, cl_plane, top_plane] + pl_transom + pl_foreend

#puts "Build solid from shell..."
#hullsolid = Build.solid hullsolid
#
#puts "Save solid model to file..."
#BRepIO.save hullsolid, "/tmp/#{no}.brep"

puts "Done."

