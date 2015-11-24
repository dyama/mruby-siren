#
# Array クラス拡張メソッド
#
class Array

  def to_v
    if size == 0
      Vec::zero
    else
      Vec::new self.x, self.y, self.z
    end
  end

  def trans(t)
    t.move_point self
  end

  def trans!(t)
    r = t.move_point self
    x = r.x, y = r.y, z = r.z
  end

  def x
    val = (self[0] ||= 0.0)
    val.is_a?(Float) ? val : val.to_f
  end
  def y
    val = (self[1] ||= 0.0)
    val.is_a?(Float) ? val : val.to_f
  end
  def z
    val = (self[2] ||= 0.0)
    val.is_a?(Float) ? val : val.to_f
  end

  def x=(val); self[0] = val end
  def y=(val); self[1] = val end
  def z=(val); self[2] = val end

end

