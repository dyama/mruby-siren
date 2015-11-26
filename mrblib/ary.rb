#
# Array クラス拡張メソッド
#
class Array

  def to_v
    Vec::new self
  end

  def to(other)
    other.to_v - self.to_v
  end

  def from(other)
    self.to_v - other.to_v
  end

  def xyz
    self[0,3]
  end

  def xyz=(val)
    self[0,3] = val
  end

  def dist(other)
    (self.to_v - other.to_v).magnitude
  end

  def center(other)
    ((self.to_v + other.to_v) / 2.0).xyz
  end

  def equal?(other, lintol)
    dist(other) < lintol
  end

  def translate(t)
    if t.is_a? Vec
      v = t
    else
      v = t.to_v
    end
    (self.to_v + v).xyz
  end

  def translate!(t)
    self.xyz = translate(t)
  end

  def rotate(op, dir, angle)
    self.from(op).rotate(dir, angle).xyz.translate(op).xyz
  end

  def rotate!(op, dir, angle)
    self.xyz = rotate(op, dir, angle)
  end

  def scale(op, f)
    if (op.equal?(self, 1.0e-7))
      self.xyz
    else
      (self.from(op).normal * f).xyz.translate(op).xyz
    end
  end

  def scale!(op, f)
    self.xyz = scale(op, f)
  end

  def mirror(op, dir=Vec::zero)
    if dir == Vec::zero
      op.translate(self.to(op)).xyz
    else
      self.from(op).mirror(dir).xyz.translate(op).xyz
    end
  end

  def mirror!(op, dir=Vec::zero)
    self.xyz = mirror(op, dir)
  end

  def trans(t)
    t.move_point self
  end

  def trans!(t)
    r = t.move_point self
    xyz = r.xyz
  end

  def x
    val = (self[0] ||= 0.0)
    if val.is_a?(Float)
      val
    elsif val.is_a?(Numeric)
      val.to_f
    else
      0.0
    end
  end

  def y
    val = (self[1] ||= 0.0)
    if val.is_a?(Float)
      val
    elsif val.is_a?(Numeric)
      val.to_f
    else
      0.0
    end
  end

  def z
    val = (self[2] ||= 0.0)
    if val.is_a?(Float)
      val
    elsif val.is_a?(Numeric)
      val.to_f
    else
      0.0
    end
  end

  def x=(val); self[0] = val end
  def y=(val); self[1] = val end
  def z=(val); self[2] = val end

end

