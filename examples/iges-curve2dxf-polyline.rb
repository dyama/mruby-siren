#!/usr/bin/siren
# coding: utf-8
#
# IGES curve to DXF polyline
#

# DXF データ要素の書式付き出力
def ds(no, val)
  sprintf("%3d\n", no) +
    (val.is_a?(Float) ? sprintf("%14.6f\n", val) : "#{val}\n")
end

# Array クラス拡張
class Array
  def to_dxf
    s = ""
    s += ds 10, self.x
    s += ds 20, self.y
    s += ds 30, self.z
  end
end

# Shape クラス拡張
class Shape

  # レイヤー名 アクセサ
  def layer; @layer end
  def layer=(value); @layer=value end

  # DXF ポリライン出力
  def to_polyline
    s = ""
    # エッジ単位で処理
    self.explore(ShapeType::EDGE) do |edge|
      s += ds 0, "POLYLINE"  
      s += ds 6, 3
      s += ds 8, @layer
      s += ds 66, 1
      s += ds 70, 8
      s += [].to_dxf
      # 点列化
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
  # IGES の読み込み・DXF ポリラインの出力
  IGES.load("hammer.iges").each do |shape|
    shape.layer = "BASE"
    f.write shape.to_polyline
  end
  f.write ds(0, "ENDSEC")
  f.write ds(0, "EOF")
end

puts "done."

