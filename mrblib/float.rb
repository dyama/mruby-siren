#
# Float クラス拡張メソッド
#
class Float

  def to_deg
    self * 180.0 / Math::PI
  end

  def to_rad
    self * Math::PI / 180.0
  end

end

