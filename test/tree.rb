
$lines = []
$len = 100.0

def tree(pt, d, l)
  pp = pt + d * l
  e = Build::line(pt, pp)
  $lines.push(e)
  if l < $len / 10.0
    return 1
  end
  l = l * 0.75
  tree(pp, d.rotate(Vec::origin, Vec::ydir, Math::PI / 6.0), l)
  tree(pp, d.rotate(Vec::origin, Vec::ydir, -Math::PI / 6.0), l)
end

tree Vec::origin, Vec::zdir, $len

comp = Build.compound $lines
IGES.save [comp], "test.igs"

