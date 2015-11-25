#!/usr/bin/siren
# coding: utf-8
#
# IGES curve to DXF polyline
#

# DXF �f�[�^�v�f�̏����t���o��
def ds(no, val)
  sprintf("%3d\n", no) +
    (val.is_a?(Float) ? sprintf("%14.6f\n", val) : "#{val}\n")
end

# Array �N���X�g��
class Array
  def to_dxf
    s = ""
    s += ds 10, self.x
    s += ds 20, self.y
    s += ds 30, self.z
  end
end

# Shape �N���X�g��
class Shape

  # ���C���[�� �A�N�Z�T
  def layer; @layer end
  def layer=(value); @layer=value end

  # DXF �|�����C���o��
  def to_polyline
    s = ""
    # �G�b�W�P�ʂŏ���
    self.explore(ShapeType::EDGE) do |edge|
      s += ds 0, "POLYLINE"  
      s += ds 6, 3
      s += ds 8, @layer
      s += ds 66, 1
      s += ds 70, 8
      s += [].to_dxf
      # �_��
      edge.to_pts.each do |pnt|
        s += ds 0, "VERTEX"
        s += ds 8, @layer
        s += pnt.to_dxf
      end
      s += ds 0, "SEQEND"
      s += ds 8, @layer
    end
    return s
  end
end

File.open("hammer.dxf", "w") do |f|
  f.write ds(0, "SECTION")
  f.write ds(2, "ENTITIES")
  # IGES �̓ǂݍ��݁EDXF �|�����C���̏o��
  IGES.load("hammer.iges").each do |shape|
    shape.layer = "BASE"
    f.write shape.to_polyline
  end
  f.write ds(0, "ENDSEC")
  f.write ds(0, "EOF")
end

puts "done."

