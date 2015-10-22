##
# ジオメトリカーブタイプ 定義モジュール
#
module GeomCurveType

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
  def self.to_s(type)
    case type
    when GeomCurveType::BEZIERCURVE
      return "BEZIERCURVE"
    when GeomCurveType::BSPLINECURVE
      return "BSPLINECURVE"
    when GeomCurveType::TRIMMEDCURVE
      return "TRIMMEDCURVE"
    when GeomCurveType::CIRCLE
      return "CIRCLE"
    when GeomCurveType::ELLIPSE
      return "ELLIPSE"
    when GeomCurveType::HYPERBOLA
      return "HYPERBOLA"
    when GeomCurveType::PARABOLA
      return "PARABOLA"
    when GeomCurveType::CONIC
      return "CONIC"
    when GeomCurveType::LINE
      return "LINE"
    when GeomCurveType::OFFSETCURVE
      return "OFFSETCURVE"
    when GeomCurveType::COMPLEXCURVE
      return "COMPLEXCURVE"
    else
      return "UNKNOWN"
    end
  end

  #
  # カーブ名文字列をジオメトリカーブタイプ(番号)にする
  #
  def self.to_i(typename)
    case typename
    when "BEZIERCURVE"
      return GeomCurveType::BEZIERCURVE
    when "BSPLINECURVE"
      return GeomCurveType::BSPLINECURVE
    when "TRIMMEDCURVE"
      return GeomCurveType::TRIMMEDCURVE
    when "CIRCLE"
      return GeomCurveType::CIRCLE
    when "ELLIPSE"
      return GeomCurveType::ELLIPSE
    when "HYPERBOLA"
      return GeomCurveType::HYPERBOLA
    when "PARABOLA"
      return GeomCurveType::PARABOLA
    when "CONIC"
      return GeomCurveType::CONIC
    when "LINE"
      return GeomCurveType::LINE
    when "OFFSETCURVE"
      return GeomCurveType::OFFSETCURVE
    when "COMPLEXCURVE"
      return GeomCurveType::COMPLEXCURVE
    else
      raise "No such typename"
    end
  end

end

class Integer
  def to_gcname
    GeomCurveType::to_s(self)
  end
end

class String
  def to_gcno
    GeomCurveType::to_i(self)
  end
end

