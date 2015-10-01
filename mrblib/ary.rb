#
# Array クラス拡張メソッド
#
class Array

  def to_v
    if size == 0
      Vec::new 0.0, 0.0, 0.0
    else
      x = 0.0, y = 0.0, z = 0.0
      if size > 0 then x = self[0].to_f end
      if size > 1 then y = self[1].to_f end
      if size > 2 then z = self[2].to_f end
      Vec::new x, y, z
    end
  end

  def trans(t)
    t.move_point self
  end

  def trans!(t)
    r = t.move_point self
    x = r.x, y = r.y, z = r.z
  end

  def x; (self[0] ||= 0).to_f end
  def y; (self[1] ||= 0).to_f end
  def z; (self[2] ||= 0).to_f end

  def x=(val); self[0] = val end
  def y=(val); self[1] = val end
  def z=(val); self[2] = val end

end

