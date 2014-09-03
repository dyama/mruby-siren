
# 1. Offset table csv to surface/solid model.
# 2. Calculation hydrostatics table with solid model.

ofsfile = "/tmp/TABLE.csv"
lpp = 123.4

no = ""
sl = []
t = Hash.new

# Parse
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

# Make hullshape surface
ws = Array.new
t.each do |x, ln|
  x = x * 22.4 / 10
  pts = Array.new
  ln.each do |z, y|
    pts.push Vec.new(x, y, z)
  end
  ws.push Build.polyline(pts)
end
res = Offset.loft ws



BRepIO.save res, "/tmp/#{no}.brep"
puts "Done."

