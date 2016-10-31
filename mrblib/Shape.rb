#
# Shape クラス拡張メソッド
#
class Siren::Shape

  # Explorer wrapper methods

  def compounds(filter = nil)
    if filter
      self.explore(Siren::Compound, filter)
    else
      self.explore(Siren::Compound)
    end
  end

  def solids(filter = nil)
    if filter
      self.explore(Siren::Solid, filter)
    else
      self.explore(Siren::Solid)
    end
  end

  def shells(filter = nil)
    if filter
      self.explore(Siren::Shell, filter)
    else
      self.explore(Siren::Shell)
    end
  end

  def faces(filter = nil)
    if filter
      self.explore(Siren::Face, filter)
    else
      self.explore(Siren::Face)
    end
  end

  def wires(filter = nil)
    if filter
      self.explore(Siren::Wire, filter)
    else
      self.explore(Siren::Wire)
    end
  end

  def edges(filter = nil)
    if filter
      self.explore(Siren::Edge, filter)
    else
      self.explore(Siren::Edge)
    end
  end

  def vertices(filter = nil)
    if filter
      self.explore(Siren::Vertex, filter)
    else
      self.explore(Siren::Vertex)
    end
  end

  # Type check methods

  def compound?
    self.is_a? Siren::Compound
  end

  def solid?
    self.is_a? Siren::Solid
  end

  def shell?
    self.is_a? Siren::Shell
  end

  def face?
    self.is_a? Siren::Face
  end

  def wire?
    self.is_a? Siren::Wire
  end

  def edge?
    self.is_a? Siren::Edge
  end

  def vertex?
    self.is_a? Siren::Vertex
  end

  def dump_tree(current_depth = 0, &limit)
    hc = sprintf("%06X", self.hashcode(0xFFFFFF))
    type = self.class.to_s
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
