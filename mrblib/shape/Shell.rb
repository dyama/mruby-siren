#
# Shell クラス拡張メソッド
#
class Siren::Shell

  def area
    self.faces.inject { |e| e.area }
  end

  def self.tol
    @@tol
  end

  def self.tol=(val)
    @@tol = val
  end

  @@tol = 1.0e-7

end

