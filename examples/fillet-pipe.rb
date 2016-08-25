#!/usr/bin/siren

# 半径を指定して内接円弧を作成する
def fillet(p1, p2, cp, r)

  ls1 = p1.to_v - cp.to_v
  ls2 = p2.to_v - cp.to_v
  cp = cp.to_v

  # 2直線のなす角度
  ang_rad = ls1.angle(ls2)
  if ang_rad.abs < 0.001
    return nil
  end

  # 交点から開始・終了点までの距離
  a = Math.tan(Math::PI / 2 - ang_rad / 2) * r

  # 始点
  startp = cp + (ls1.normal * a)

  # 終点
  termp = cp + (ls2.normal * a)

  # 2等分線ベクトル
  v = (startp - cp).normal + (termp - cp).normal
  v.normal!

  # 交点から中心点までの距離
  b = r / Math.cos(Math::PI / 2 - ang_rad / 2);

  # 中心点
  centerp = cp + (v * b);

  # 通過点
  thrup = centerp + (-v * r);

  return Build.arc3p startp, thrup, termp
end

# パイプの径
pipe_r = 1.0

# エルボの径
elbow_r = 2.0

# パイプの経路
pts = [[0, 0, 0], [10, 0, 0], [10, 10, 6], [15, 10, 10], [20, 15, 10]]


# 経路パスを作成
edges = []
pts.each_cons(3) do |ar|
  arc = fillet(ar[0], ar[2], ar[1], elbow_r)
  if edges.size == 0
    edges.push Build.line(ar[0], arc.sp)
  else
    edges.push Build.line(edges.last.tp, arc.sp)
  end
  edges.push arc
end
edges.push Build.line(edges.last.tp, pts.last)
path = Build.wire edges, 0.01

# 配管のモデル化
profile = Build.circle [], [1], pipe_r
pipe = Offset.pipe profile, path, 0, true

# 保存
BRepIO.save pipe, "pipe.brep"

puts "done"

