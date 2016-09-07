#
# Vec クラス拡張メソッド
#
class Siren::Vec

  def self.zero
    Siren::Vec.new [0.0, 0.0, 0.0]
  end

  def self.x
    Siren::Vec.new [1.0, 0.0, 0.0]
  end

  def self.y
    Siren::Vec.new [0.0, 1.0, 0.0]
  end

  def self.z
    Siren::Vec.new [0.0, 0.0, 1.0]
  end

  def self.xy
    Siren::Vec.new [1.0, 1.0, 0.0]
  end

  def self.xz
    Siren::Vec.new [1.0, 0.0, 1.0]
  end

  def self.yx
    Siren::Vec.new [1.0, 1.0, 0.0]
  end

  def self.yz
    Siren::Vec.new [0.0, 1.0, 1.0]
  end

  def self.zx
    Siren::Vec.new [1.0, 0.0, 1.0]
  end

  def self.zy
    Siren::Vec.new [0.0, 1.0, 1.0]
  end

  def self.xyz
    Siren::Vec.new [1.0, 1.0, 1.0]
  end

  def self.xdir
    Siren::Vec.x
  end

  def self.ydir
    Siren::Vec.y
  end

  def self.zdir
    Siren::Vec.z
  end

end
