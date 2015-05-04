##
# シェイプタイプ 定義モジュール
#
module ShapeType

  # コンパウンド
  COMPOUND  = 0
  # コンポジット ソリッド
  COMPSOLID = 1
  # ソリッド
  SOLID     = 2
  # シェル
  SHELL     = 3
  # フェイス
  FACE      = 4
  # ワイヤー
  WIRE      = 5
  # エッジ
  EDGE      = 6
  # バーテックス
  VERTEX    = 7
  # シェイプ
  SHAPE     = 8

  #
  # シェイプタイプ(番号)をシェイプ名文字列にする
  #
  def self.to_s(type)
    case type
    when ShapeType::COMPOUND
      return "COMPOUND"
    when ShapeType::COMPSOLID
      return "COMPSOLID"
    when ShapeType::SOLID
      return "SOLID"
    when ShapeType::SHELL
      return "SHELL"
    when ShapeType::FACE
      return "FACE"
    when ShapeType::WIRE
      return "WIRE"
    when ShapeType::EDGE
      return "EDGE"
    when ShapeType::VERTEX
      return "VERTEX"
    when ShapeType::SHAPE
      return "SHAPE"
    else
      return "UNKNOWN"
    end
  end

  #
  # シェイプ名をシェイプタイプ(番号)にする
  #
  def self.to_i(typename)
    case typename
    when "COMPOUND"
      return ShapeType::COMPOUND
    when "COMPSOLID"
      return ShapeType::COMPSOLID
    when "SOLID"
      return ShapeType::SOLID
    when "SHELL"
      return ShapeType::SHELL
    when "FACE"
      return ShapeType::FACE
    when "WIRE"
      return ShapeType::WIRE
    when "EDGE"
      return ShapeType::EDGE
    when "VERTEX"
      return ShapeType::VERTEX
    when "SHAPE"
      return ShapeType::SHAPE
    else
      raise "No such typename"
    end
  end

end

class Integer
  def to_sname
    ShapeType::to_s(self)
  end
end

class String
  def to_sno
    ShapeType::to_i(self)
  end
end

