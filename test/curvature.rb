#!/usr/bin/env siren
# coding: utf-8

# unit = 1m

# 適当な構成点を与えて曲線を発生
# (入出力ベクトルは省略)
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

# 以下、表示
window = X11Window::new
world = World.new `echo $DISPLAY`.chomp
cam = Camera::new world, window.handle

s_cvs = Skin.new Build.compound cvs
s_cvs.color = ColorName::WHITE
world.add s_cvs

s_c = Skin.new c
s_c.color = ColorName::RED
world.add s_c

s_pl = Skin.new Build.polyline(pps)
s_pl.color = ColorName::GREEN
world.add s_pl

# 視点・視野設定
cam.proj = OrientType::Xneg
cam.fitz
cam.fit

# Enter が押されたら終了
STDIN.gets
