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

  ##
  # Return this object as a string.
  def to_s
    "#<Vec:0x%x @x=%f, @y=%f, @z=%f>" % [self.object_id, self.x, self.y, self.z]
  end
  alias_method :inspect, :to_s

  ##
  # Return x, y and z values of this object as an array.
  def to_a
    [self.x, self.y, self.z]
  end
  alias_method :to_ary, :to_a
  alias_method :xyz,    :to_a

end
