#!/usr/bin/siren
# coding: utf-8
#
# fractal tree
#

$start_len = 100.0

def tree(cur_pt, dir, len)
  nxt_pt = cur_pt + dir * len
  edges = [ Build.line(cur_pt, nxt_pt) ]
  len *= 0.75
  if len > $start_len / 10.0
    edges.concat tree(nxt_pt, dir.rotate(Vec.ydir, 30.0.to_rad), len)
    edges.concat tree(nxt_pt, dir.rotate(Vec.ydir, -30.0.to_rad), len)
  end
  return edges
end

lines = tree([0, 0, 0].to_v, Vec.zdir, $start_len)

comp = Build.compound lines
BRepIO.save comp, "tree.brep"

puts "done."

