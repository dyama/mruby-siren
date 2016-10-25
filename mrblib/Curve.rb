#
# Curve クラス拡張メソッド
#
class Siren::Curve

  UNKNOWN      = 0
  BEZIERCURVE  = 1
  BSPLINECURVE = 2
  TRIMMEDCURVE = 3
  BOUNDEDCURVE = 4
  CIRCLE       = 5
  ELLIPSE      = 6
  HYPERBOLA    = 7
  PARABOLA     = 8
  CONIC        = 9
  LINE         = 10
  OFFSETCURVE  = 11
  COMPLEXCURVE = 12

  #
  # ジオメトリカーブタイプ(番号)をカーブ名文字列にする
  #
  def self.typename(type)
    case type
    when Siren::Curve::BEZIERCURVE
      return "BEZIERCURVE"
    when Siren::Curve::BSPLINECURVE
      return "BSPLINECURVE"
    when Siren::Curve::TRIMMEDCURVE
      return "TRIMMEDCURVE"
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
    when Siren::Curve::OFFSETCURVE
      return "OFFSETCURVE"
    when Siren::Curve::COMPLEXCURVE
      return "COMPLEXCURVE"
    else
      return "UNKNOWN"
    end
  end

end
