#!siren
# coding: utf-8

include Siren

lpp = 158.0
b   = 27.0 * 1.2
b2  = b / 2.0
b4  = b / 4.0
d   = 14.4
ae  = -3.5
loa = 166.575 + ae
ms  = lpp / 2.0
pp_aft  = ms - 20.035
pp_fore = ms + 32.077
pp_len = pp_fore - pp_aft;
br = 1.8

lines = []
faces = []

xtop_max = lpp + (loa - lpp) / 3.0

# パラレルパート
bilge = arc [0, b2-br, br], Vec.xdir, -Vec.zdir, br, 0.0.to_rad, 90.0.to_rad
para_bl = line [0, 0], [0, b2-br]
para_sl = line [0, b2, br], [0, b2, d]
paraw = wire [para_bl, bilge, para_sl], 0.01
parawa = copy paraw
parawa.translate! [pp_aft]
parawf = copy paraw
parawf.translate! [pp_fore]
para = loft [parawa, parawf]
lines << parawa << parawf
faces << para

# アフトガンネルライン
av = [(pp_aft - ae) / 4.0, b2].to_v - [ae, b4].to_v
av.normal!
ptsa = [ [ae, b4, d], [pp_aft - (pp_aft - ae) / 2.0, b2, d]]
vcsa = [ av.to_a, [pp_len / 2.0, 0.0]]
gunnela = interpolate(ptsa, vcsa)
lines << gunnela

# フォアガンネルライン
fv = [xtop_max - pp_fore, 0].to_v - [(xtop_max - pp_fore) * 3.0 / 4.0, b2].to_v
ptsf = [[pp_fore + (xtop_max - pp_fore) / 3.0, b2, d], [xtop_max, 0, d] ]
vcsf = [ [pp_len / 2.0, 0.0], fv.to_a ]
gunnelf = interpolate(ptsf, vcsf)
lines << gunnelf

# サイドデッドフラットライン
sdfpa = [pp_aft - (pp_aft - ae) / 2.0, b2, d]
sdfpf = [pp_fore + (xtop_max - pp_fore) / 3.0, b2, d]
sdfla = interpolate [sdfpa, [pp_aft - (pp_aft-ae) / 3.0, b2, d / 2.0], [pp_aft, b2, br]], [[0,0,-1],nil,[1,0,0]]
sdflf = interpolate [[pp_fore, b2, br], sdfpf], [[1,0,0],[0,0,1]]
lines << sdfla << sdflf

# ボトムデッドフラットライン
blae = [-ae + -ae / 5.0, 0, 0]
blfe = [lpp - (loa-lpp)/2.0, 0, 0]
bdfla = interpolate [blae, [pp_aft, b2 - br, 0]], [[1,0,0],[1,0,0]]
bdflf = interpolate [[pp_fore, b2 - br, 0], blfe], [[1,0,0],[1,-0.5,0]]
lines << bdfla << bdflf

# トランサム
tsom_tl = line([ae, 0, d], [ae, b4, d])
tsom_bl = interpolate [[ae, 0, d * 2.0 / 3.0], [ae, b4, d]], [[0,1,0], [0,0,1]]
lines << tsom_tl << tsom_bl

# アフト プロファイル
v1 = [-ae, 0, d / 2.0].to_v - [ae, 0, d * 2.0 / 3.0].to_v
v1.normal!
v2 = v1.rotate(Vec.ydir, 90.0.to_rad)
v2.normal!
tp = line [ae, 0, d],[ae, 0, d * 2.0 / 3.0]
tp2 = line [ae, 0, d * 2.0 / 3.0], [-ae, 0, d / 2.0]
tp3 = interpolate [[-ae, 0, d / 2.0], [-ae + -ae / 5.0, 0, d / 4.0]], [v1.to_a, v2.to_a]
tp4 = line [-ae + -ae / 5.0, 0, d / 4.0], blae
aft_profile = wire [tp, tp2, tp3, tp4], 0.01
lines << aft_profile

# フォア プロファイル
p1 = blfe
p2 = [loa, 0, d * 0.3]
p3 = [lpp, 0, d / 4.0 * 2.5]
p4 = [lpp, 0, d / 4.0 * 3.0]
p5 = [xtop_max, 0, d]
fore_profile = interpolate [p1, p2, [xtop_max,0,d/2.0], p3, p4, p5], [[1,0,0], [0,0,1], nil, [0,0,1], [0,0,1], (p5.to_v - p4.to_v).to_a]
lines << fore_profile

# ボトム面(アフト)
bottom_aft_plane_contour = wire [bdfla, para_bl.translate([pp_aft]), line(blae, [pp_aft])]
bottom_aft_plane = face bottom_aft_plane_contour, true
faces << bottom_aft_plane

# ボトム面(フォア)
bottom_fore_plane_contour = wire [bdflf, para_bl.translate([pp_fore]), line(blfe, [pp_fore])]
faces << face(bottom_fore_plane_contour, true)

# サイド面(アフト)
side_aft_plane_contour = wire [sdfla, para_sl.translate([pp_aft]), line([pp_aft,b2,d],sdfpa)]
faces << face(side_aft_plane_contour, true)

# サイド面(フォア)
side_fore_plane_contour = wire [sdflf, para_sl.translate([pp_fore]), line([pp_fore,b2,d],sdfpf)]
faces << face(side_fore_plane_contour, true)

# トランサム面
transom_plane_contour = wire [tsom_tl, tsom_bl, line([ae,0,d], [ae,0,d*2.0/3.0])], 0.01
faces << face(transom_plane_contour, true)

if false
  # 上甲板面
  updk_plane_contour = wire [tsom_tl, gunnela, line(sdfpa, sdfpf), gunnelf, line([xtop_max,0,d], [ae, 0, d]) ], 0.01
  faces << face(updk_plane_contour, true)

  # CL面
  cl_plane_contour = wire [aft_profile, line([ae, 0, d], [xtop_max, 0, d]), fore_profile, line(blfe, blae) ], 0.01
  faces << face(cl_plane_contour, true)
end

# アフト曲面
fa = Filler.new
[tsom_bl, gunnela, sdfla, bilge.translate([pp_aft]), bdfla, tp4, tp3, tp2].each do |edge|
  fa.add_bound edge, 0
end
fa.build
if fa.done?
  faces << fa.face
end

# フォア曲面
ff = Filler.new
[bdflf, bilge.translate([pp_fore]), sdflf, gunnelf, fore_profile].each do |edge|
  ff.add_bound edge, 0
end
ff.build
if ff.done?
  faces << ff.face
end

# shell = sewing faces, 0.01
# solid = solid shell

# 出力
comp = Compound.new lines
save_brep comp, "curves.brep"

comp = Compound.new faces
save_brep comp, "faces.brep"

