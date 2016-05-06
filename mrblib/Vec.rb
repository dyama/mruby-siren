#
# Vec クラス拡張メソッド
#
class Vec

  def self.zero
    Vec.new [0.0, 0.0, 0.0]
  end

  def self.x
    Vec.new [1.0, 0.0, 0.0]
  end

  def self.y
    Vec.new [0.0, 1.0, 0.0]
  end

  def self.z
    Vec.new [0.0, 0.0, 1.0]
  end

  def self.xy
    Vec.new [1.0, 1.0, 0.0]
  end

  def self.xz
    Vec.new [1.0, 0.0, 1.0]
  end

  def self.yx
    Vec.new [1.0, 1.0, 0.0]
  end

  def self.yz
    Vec.new [0.0, 1.0, 1.0]
  end

  def self.zx
    Vec.new [1.0, 0.0, 1.0]
  end

  def self.zy
    Vec.new [0.0, 1.0, 1.0]
  end

  def self.xyz
    Vec.new [1.0, 1.0, 1.0]
  end

  def self.xdir
    Vec.x
  end

  def self.ydir
    Vec.y
  end

  def self.zdir
    Vec.z
  end

end
