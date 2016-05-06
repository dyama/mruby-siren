#
# Vec クラス拡張メソッド
#
class Vec

  def self.zero
    Vec.new [0.0, 0.0, 0.0]
  end

  def self.xdir
    Vec.new [1.0, 0.0, 0.0]
  end

  def self.ydir
    Vec.new [0.0, 1.0, 0.0]
  end

  def self.zdir
    Vec.new [0.0, 0.0, 1.0]
  end

end
