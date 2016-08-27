#!/usr/bin/siren
# coding: utf-8
#
# 交線 発生サンプル
#

include Siren

tor = torus [0, 0, 0], Vec.zdir, 30, 10, Math::PI * 2
pln = infplane [0, 0, 0], [0.5, 0.3, 0.8].to_v.normal
int_curve = tor.section(pln)

faces = []
int_curve.edges do |e|
  w = wire [e]
  faces << face(w, true)
end

comp = compound faces
save_brep comp, "int.brep"
save_brep tor, "torus.brep"

