#!/usr/bin/siren

# ���a���w�肵�ē��ډ~�ʂ��쐬����
def fillet(p1, p2, cp, r)

  ls1 = p1.to_v - cp.to_v
  ls2 = p2.to_v - cp.to_v
  cp = cp.to_v

  # 2�����̂Ȃ��p�x
  ang_rad = ls1.angle(ls2)
  if ang_rad.abs < 0.001
    return nil
  end

  # ��_����J�n�E�I���_�܂ł̋���
  a = Math.tan(Math::PI / 2 - ang_rad / 2) * r

  # �n�_
  startp = cp + (ls1.normal * a)

  # �I�_
  termp = cp + (ls2.normal * a)

  # 2�������x�N�g��
  v = (startp - cp).normal + (termp - cp).normal
  v.normal!

  # ��_���璆�S�_�܂ł̋���
  b = r / Math.cos(Math::PI / 2 - ang_rad / 2);

  # ���S�_
  centerp = cp + (v * b);

  # �ʉߓ_
  thrup = centerp + (-v * r);

  return Build.arc3p startp, thrup, termp
end

# �p�C�v�̌a
pipe_r = 1.0

# �G���{�̌a
elbow_r = 2.0

# �p�C�v�̌o�H
pts = [[0, 0, 0], [10, 0, 0], [10, 10, 6], [15, 10, 10], [20, 15, 10]]


# �o�H�p�X���쐬
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

# �z�ǂ̃��f����
profile = Build.circle [], [1], pipe_r
pipe = Offset.pipe profile, path, 0, true

# �ۑ�
BRepIO.save pipe, "pipe.brep"

puts "done"

