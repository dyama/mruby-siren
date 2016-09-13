#
# Shape クラス拡張メソッド
#
class Siren::Shape

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
    when Siren::Shape::COMPOUND
      return "COMPOUND"
    when Siren::Shape::COMPSOLID
      return "COMPSOLID"
    when Siren::Shape::SOLID
      return "SOLID"
    when Siren::Shape::SHELL
      return "SHELL"
    when Siren::Shape::FACE
      return "FACE"
    when Siren::Shape::WIRE
      return "WIRE"
    when Siren::Shape::EDGE
      return "EDGE"
    when Siren::Shape::VERTEX
      return "VERTEX"
    when Siren::Shape::SHAPE
      return "SHAPE"
    else
      return "UNKNOWN"
    end
  end

  # Explorer wrapper methods

  def compounds(filter = nil)
    if filter
      self.explore(Siren::Shape::COMPOUND, filter)
    else
      self.explore(Siren::Shape::COMPOUND)
    end
  end

  def compsolids(filter = nil)
    if filter
      self.explore(Siren::Shape::COMPSOLID, filter)
    else
      self.explore(Siren::Shape::COMPSOLID)
    end
  end

  def solids(filter = nil)
    if filter
      self.explore(Siren::Shape::SOLID, filter)
    else
      self.explore(Siren::Shape::SOLID)
    end
  end

  def shells(filter = nil)
    if filter
      self.explore(Siren::Shape::SHELL, filter)
    else
      self.explore(Siren::Shape::SHELL)
    end
  end

  def faces(filter = nil)
    if filter
      self.explore(Siren::Shape::FACE, filter)
    else
      self.explore(Siren::Shape::FACE)
    end
  end

  def wires(filter = nil)
    if filter
      self.explore(Siren::Shape::WIRE, filter)
    else
      self.explore(Siren::Shape::WIRE)
    end
  end

  def edges(filter = nil)
    if filter
      self.explore(Siren::Shape::EDGE, filter)
    else
      self.explore(Siren::Shape::EDGE)
    end
  end

  def vertices(filter = nil)
    if filter
      self.explore(Siren::Shape::VERTEX, filter)
    else
      self.explore(Siren::Shape::VERTEX)
    end
  end

  # Type check methods

  def compound?
    self.shapetype == Siren::Shape::COMPOUND
  end

  def compsolid?
    self.shapetype == Siren::Shape::COMPSOLID
  end

  def solid?
    self.shapetype == Siren::Shape::SOLID
  end

  def shell?
    self.shapetype == Siren::Shape::SHELL
  end

  def face?
    self.shapetype == Siren::Shape::FACE
  end

  def wire?
    self.shapetype == Siren::Shape::WIRE
  end

  def edge?
    self.shapetype == Siren::Shape::EDGE
  end

  def vertex?
    self.shapetype == Siren::Shape::VERTEX
  end

  def dump_tree(current_depth = 0, &limit)
    hc = sprintf("%06X", self.hashcode(0xFFFFFF))
    type = Siren::Shape.typename(self.shapetype)
    puts "  " * current_depth + "%s:0x%s" % [type, hc]
    if limit && limit.call(current_depth, self)
      # puts "  " * current_depth + "..."
      return
    end
    current_depth += 1
    self.subshapes.each do |s|
      s.dump_tree(current_depth, &limit)
    end
    nil
  end

  def dump_compound
    self.dump_tree{|depth, child| child.compound?}
  end

  def dump_solid
    self.dump_tree{|depth, child| child.solid?}
  end

  def dump_shell
    self.dump_tree{|depth, child| child.sell?}
  end

  def dump_face
    self.dump_tree{|depth, child| child.face?}
  end

  def dump_wire
    self.dump_tree{|depth, child| child.wire?}
  end

  def dump_edge
    self.dump_tree{|depth, child| child.edge?}
  end

  def dump_vertex
    self.dump_tree{|depth, child| child.vertex?}
  end

  def clone(copy_geom = true)
    Siren.copy(self, copy_geom)
  end

  def to_a
    if self.compound?
      ar = []
      self.subshapes.each do |s|
        if s.compound?
          ar << s.to_a
        else
          ar.push s
        end
      end
      return ar
    else
      return [self]
    end
  end

end
