#!/usr/bin/siren
# coding: utf-8

ress = []

  # lines of Hull
  wl = [
    [[1.0,0,6],[1,1,6],[3,2,6],[6,3,6],[10,4,6],[13,4.5,6],[20,5.0,6],[30,5.5,6],[40,5.5,6],[50,5.5,6],[60,5.5,6],[70,5.5,6],[80,5.5,6],[90,5.1,6.0],[100,4.5,6],[105,4.1-0.00,6],[110,3.5-0.00,6],[113,2.9-0.00,6],[116,2.0-0.00,6],[119-0.0,0.9-0.00,6],[120+0.9,0,6]],
    [[0.7,0,5],[1,1,5],[3,2,5],[6,3,5],[10,4,5],[13,4.5,5],[20,5.0,5],[30,5.5,5],[40,5.5,5],[50,5.5,5],[60,5.5,5],[70,5.5,5],[80,5.5,5],[90,5.1,5.0],[100,4.5,5],[105,4.1-0.10,5],[110,3.5-0.10,5],[113,2.9-0.10,5],[116,2.0-0.12,5],[119-0.2,0.9-0.10,5],[120+0.4,0,5]],
    [[0.5,0,4],[1,1,4],[3,2,4],[6,3,4],[10,4,4],[13,4.5,4],[20,5.0,4],[30,5.5,4],[40,5.5,4],[50,5.5,4],[60,5.5,4],[70,5.5,4],[80,5.5,4],[90,5.1,4,0],[100,4.5,4],[105,4.1-0.16,4],[110,3.5-0.16,4],[113,2.9-0.18,4],[116,2.0-0.23,4],[119-0.4,0.9-0.16,4],[120+0.0,0,4]],
    [[0.3,0,3],[1,1,3],[3,2,3],[6,3,3],[10,4,3],[13,4.5,3],[20,5.0,3],[30,5.5,3],[40,5.5,3],[50,5.5,3],[60,5.5,3],[70,5.5,3],[80,5.5,3],[90,5.1,3.0],[100,4.5,3],[105,4.1-0.20,3],[110,3.5-0.20,3],[113,2.9-0.24,3],[116,2.0-0.33,3],[119-0.6,0.9-0.20,3],[120-0.3,0,3]],
    [[0.2,0,2],[1,1,2],[3,2,2],[6,3,2],[10,4,2],[13,4.5,2],[20,5.0,2],[30,5.5,2],[40,5.5,2],[50,5.5,2],[60,5.5,2],[70,5.5,2],[80,5.5,2],[90,5.1,2.0],[100,4.5,2],[105,4.1-0.22,2],[110,3.5-0.22,2],[113,2.9-0.29,2],[116,2.0-0.42,2],[119-0.8,0.9-0.22,2],[120-0.5,0,2]],
    [[0.1,0,1],[1,1,1],[3,2,1],[6,3,1],[10,4,1],[13,4.5,1],[20,5.0,1],[30,5.5,1],[40,5.5,1],[50,5.5,1],[60,5.5,1],[70,5.5,1],[80,5.5,1],[90,5.1,1.0],[100,4.5,1],[105,4.1-0.23,1],[110,3.5-0.23,1],[113,2.9-0.33,1],[116,2.0-0.50,1],[119-1.0,0.9-0.23,1],[120-0.6,0,1]],
    [[0.0,0,0],[1,1,0],[3,2,0],[6,3,0],[10,4,0],[13,4.5,0],[20,5.0,0],[30,5.5,0],[40,5.5,0],[50,5.5,0],[60,5.5,0],[70,5.5,0],[80,5.5,0],[90,5.1,0.0],[100,4.5,0],[105,4.1-0.24,0],[110,3.5-0.24,0],[113,2.9-0.35,0],[116,2.0-0.56,0],[119-1.2,0.9-0.24,0],[120-0.7,0,0]]
  ]

  # port side
  hullp = Offset.loft(wl.map{|ps| Build.polyline(ps)})
  topp = Build.polygon(wl.first + [wl.first[0]])
  btmp = Build.polygon(wl.last + [wl.last[0]])

  # starboard side
  hulls, tops, btms = [hullp, topp, btmp].map{|item| item.mirror([0,0,0], Vec::ydir)}

  hullshell = Build.sewing [hullp, topp, btmp, hulls, tops, btms]
  hull = Build.solid hullshell

  # Upperdeck line
  n = -9
  a = 10
  ul = [[0,n,2.5],[83,n,2.5],[85,n,4.8],[100,n,4.8],[110,n,5.1],[116,n,5.5],[122,n,6],[122,n,a],[0,n,a],[0,n,2.5]]

  plate = Build.polygon ul
  deckbox = Offset.sweep_vec plate, Vec.new(0, -n*2, 0)
  res = hull.cut deckbox
  ress.push res

if false
  box1 = Prim::box [20, 20, 20]
  box2 = Prim::box [20, 20, 20]
  box2.translate! [5, 5, 5]
  res = box1.cut box2
  ress.push res
end

c = Build.curve([
  [0, 0, 0],     [0, 1, 0],
  [0, 2, 0.5],   [0, 3, 1.8],
  [0, 4, 3.8],   [0, 5, 5.5],
  [0, 6, 6.8],   [0, 6.5, 8.2],
  [0, 6.8, 9.5], [0, 7, 11.2],
])

# トレランス、刻みピッチ、曲率ベクトルの大きさ係数
t = 0.01 # 1cm
pt = 0.2
f = -3.0

# 始終点の曲線パラメータを取得
spr = c.param(c.sp, t)
tpr = c.param(c.tp, t)

cvs = []
pps = []

# 計算
spr.floor.step(tpr.floor, pt) do |pr|
  # パラメータにおける三次元位置
  cp = c.to_xyz pr
  # パラメータにおける曲率ベクトル
  cv = c.curvature pr
  # ベクトル同士の和差、スカラ積は未実装・・・
  # pp = cp + cv * f
  pp = [cp.x+cv.x*f, cp.y+cv.y*f, cp.z+cv.z*f]
  cvs.push Build.line(cp, pp)
  pps.push pp
end

ress.push Build.compound [c, Build.curve(pps)] + cvs

BRepIO::save Build::compound(ress), "result.brep"

