#
# Curve クラス拡張メソッド
#
class Siren::Curve

  LINE      = 0
  CIRCLE    = 1
  ELLIPSE   = 2
  HYPERBOLA = 3
  PARABOLA  = 4
  BEZIER    = 5
  BSPLINE   = 6
  OFFSET    = 7
  OTHER     = 8

  #
  # ジオメトリカーブタイプ(番号)をカーブ名文字列にする
  #
  def self.typename(type)
    case type
    when Siren::Curve::BEZIER
      return "BEZIER"
    when Siren::Curve::BSPLINE
      return "BSPLINE"
    when Siren::Curve::CIRCLE
      return "CIRCLE"
    when Siren::Curve::ELLIPSE
      return "ELLIPSE"
    when Siren::Curve::HYPERBOLA
      return "HYPERBOLA"
    when Siren::Curve::PARABOLA
      return "PARABOLA"
    when Siren::Curve::LINE
      return "LINE"
    when Siren::Curve::OFFSET
      return "OFFSET"
    else
      return "UNKNOWN"
    end
  end

  def bezier?;    self.type == Siren::Curve::BEZIER    end
  def bspline?;   self.type == Siren::Curve::BSPLINE   end
  def trimmed?;   self.type == Siren::Curve::TRIMMED   end
  def bounded?
    self.type == Siren::Curve::BOUNDED ||
      self.bezier? || self.bspline? || self.trimmed?
  end
  def circle?;    self.type == Siren::Curve::CIRCLE    end
  def ellipse?;   self.type == Siren::Curve::ELLIPSE   end
  def hyperbola?; self.type == Siren::Curve::HYPERBOLA end
  def parabola?;  self.type == Siren::Curve::PARABOLA  end
  def conic?
    self.type == Siren::Curve::CONIC ||
      self.circle? || self.ellipse? || self.hyperbola? || self.parabola?
  end
  def line?;      self.type == Siren::Curve::LINE      end
  def offset?;    self.type == Siren::Curve::OFFSET    end
  def complex?;   self.type == Siren::Curve::COMPLEX   end

end
