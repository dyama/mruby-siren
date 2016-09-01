#
# Shape クラス拡張メソッド
#
class Shape

  COMPOUND  = 0
  COMPSOLID = 1
  SOLID     = 2
  SHELL     = 3
  FACE      = 4
  WIRE      = 5
  EDGE      = 6
  VERTEX    = 7
  SHAPE     = 8

  def self.typename(type)
    case type
    when Shape::COMPOUND
      return "COMPOUND"
    when Shape::COMPSOLID
      return "COMPSOLID"
    when Shape::SOLID
      return "SOLID"
    when Shape::SHELL
      return "SHELL"
    when Shape::FACE
      return "FACE"
    when Shape::WIRE
      return "WIRE"
    when Shape::EDGE
      return "EDGE"
    when Shape::VERTEX
      return "VERTEX"
    when Shape::SHAPE
      return "SHAPE"
    else
      return "UNKNOWN"
    end
  end

  # Explorer wrapper methods

  def compounds(filter = nil)
    if filter
      self.explore(Shape::COMPOUND, filter)
    else
      self.explore(Shape::COMPOUND)
    end
  end

  def compsolids(filter = nil)
    if filter
      self.explore(Shape::COMPSOLID, filter)
    else
      self.explore(Shape::COMPSOLID)
    end
  end

  def solids(filter = nil)
    if filter
      self.explore(Shape::SOLID, filter)
    else
      self.explore(Shape::SOLID)
    end
  end

  def shells(filter = nil)
    if filter
      self.explore(Shape::SHELL, filter)
    else
      self.explore(Shape::SHELL)
    end
  end

  def faces(filter = nil)
    if filter
      self.explore(Shape::FACE, filter)
    else
      self.explore(Shape::FACE)
    end
  end

  def wires(filter = nil)
    if filter
      self.explore(Shape::WIRE, filter)
    else
      self.explore(Shape::WIRE)
    end
  end

  def edges(filter = nil)
    if filter
      self.explore(Shape::EDGE, filter)
    else
      self.explore(Shape::EDGE)
    end
  end

  def vertices(filter = nil)
    if filter
      self.explore(Shape::VERTEX, filter)
    else
      self.explore(Shape::VERTEX)
    end
  end

  # Type check methods

  def compound?
    self.shapetype == Shape::COMPOUND
  end

  def compsolid?
    self.shapetype == Shape::COMPSOLID
  end

  def solid?
    self.shapetype == Shape::SOLID
  end

  def shell?
    self.shapetype == Shape::SHELL
  end

  def face?
    self.shapetype == Shape::FACE
  end

  def wire?
    self.shapetype == Shape::WIRE
  end

  def edge?
    self.shapetype == Shape::EDGE
  end

  def vertex?
    self.shapetype == Shape::VERTEX
  end

  def dump_tree(d = 0)
    hc = sprintf("%06X", self.hashcode(0xFFFFFF))
    type = Shape.typename(self.shapetype)
    puts "  " * d + "%s:0x%s" % [type, hc]
    d += 1
    self.subshapes.each do |s|
      s.dump_tree(d)
    end
  end

  def clone(copy_geom = true)
    Siren.copy(self, copy_geom)
  end

end
