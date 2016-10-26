#
# Curve クラス拡張メソッド
#
class Siren::Curve

  UNKNOWN   = 0
  BEZIER    = 1
  BSPLINE   = 2
  TRIMMED   = 3
  BOUNDED   = 4
  CIRCLE    = 5
  ELLIPSE   = 6
  HYPERBOLA = 7
  PARABOLA  = 8
  CONIC     = 9
  LINE      = 10
  OFFSET    = 11
  COMPLEX   = 12

  #
  # ジオメトリカーブタイプ(番号)をカーブ名文字列にする
  #
  def self.typename(type)
    case type
    when Siren::Curve::BEZIER
      return "BEZIER"
    when Siren::Curve::BSPLINE
      return "BSPLINE"
    when Siren::Curve::TRIMMED
      return "TRIMMED"
    when Siren::Curve::BOUNDED
      return "BOUNDED"
    when Siren::Curve::CIRCLE
      return "CIRCLE"
    when Siren::Curve::ELLIPSE
      return "ELLIPSE"
    when Siren::Curve::HYPERBOLA
      return "HYPERBOLA"
    when Siren::Curve::PARABOLA
      return "PARABOLA"
    when Siren::Curve::CONIC
      return "CONIC"
    when Siren::Curve::LINE
      return "LINE"
    when Siren::Curve::OFFSET
      return "OFFSET"
    when Siren::Curve::COMPLEX
      return "COMPLEX"
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
