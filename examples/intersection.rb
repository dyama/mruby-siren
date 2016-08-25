#!/usr/bin/siren
# coding: utf-8
#
# 交線 発生サンプル
#

tor = Prim.torus [0, 0, 0], Vec.zdir, 30, 10, Math::PI * 2
pln = Build.infplane [0, 0, 0], [0.5, 0.3, 0.8].to_v.normal
int_curve = tor.section(pln)

faces = []
int_curve.edges do |e|
  w = Build.wire [e]
  faces << (Build.face w, true)
end

comp = Build.compound faces
BRepIO.save comp, "int.brep"
BRepIO.save tor, "torus.brep"

