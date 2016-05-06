#
# Shape クラス拡張メソッド
#
class Shape

  def conpounds(filter = nil)
    if filter
      self.explore(ShapeType::COMPOUND, filter)
    else
      self.explore(ShapeType::COMPOUND)
    end
  end

  def compsolids(filter = nil)
    self.explore(ShapeType::COMSOLID)
  end

  def solids(filter = nil)
    self.explore(ShapeType::SOLID)
  end

  def shells(filter = nil)
    self.explore(ShapeType::SHELL)
  end

  def faces(filter = nil)
    self.explore(ShapeType::FACE)
  end

  def wires(filter = nil)
    self.explore(ShapeType::WIRE)
  end

  def edges(filter = nil)
    self.explore(ShapeType::EDGE)
  end

  def vertices(filter = nil)
    self.explore(ShapeType::VERETEX)
  end

end
