#!mruby

module ShapeType

  COMPOUND  = 0
  COMPSOLID = 1
  SOLID     = 2
  SHELL     = 3
  FACE      = 4
  WIRE      = 5
  EDGE      = 6
  VERTEX    = 7
  SHAPE     = 8

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

