#
# Shape クラス拡張メソッド
#
class Shape

  # Explorer wrapper methods

  def conpounds(filter = nil)
    if filter
      self.explore(ShapeType::COMPOUND, filter)
    else
      self.explore(ShapeType::COMPOUND)
    end
  end

  def compsolids(filter = nil)
    if filter
      self.explore(ShapeType::COMSOLID, filter)
    else
      self.explore(ShapeType::COMSOLID)
    end
  end

  def solids(filter = nil)
    if filter
      self.explore(ShapeType::SOLID, filter)
    else
      self.explore(ShapeType::SOLID)
    end
  end

  def shells(filter = nil)
    if filter
      self.explore(ShapeType::SHELL, filter)
    else
      self.explore(ShapeType::SHELL)
    end
  end

  def faces(filter = nil)
    if filter
      self.explore(ShapeType::FACE, filter)
    else
      self.explore(ShapeType::FACE)
    end
  end

  def wires(filter = nil)
    if filter
      self.explore(ShapeType::WIRE, filter)
    else
      self.explore(ShapeType::WIRE)
    end
  end

  def edges(filter = nil)
    if filter
      self.explore(ShapeType::EDGE, filter)
    else
      self.explore(ShapeType::EDGE)
    end
  end

  def vertices(filter = nil)
    if filter
      self.explore(ShapeType::VERETEX, filter)
    else
      self.explore(ShapeType::VERETEX)
    end
  end

  # Type check methods

  def compound?
    self.shapetype == ShapeType::COMPOUND
  end

  def compsolid?
    self.shapetype == ShapeType::COMPSOLID
  end

  def solid?
    self.shapetype == ShapeType::SOLID
  end

  def shell?
    self.shapetype == ShapeType::SHELL
  end

  def face?
    self.shapetype == ShapeType::FACE
  end

  def wire?
    self.shapetype == ShapeType::WIRE
  end

  def edge?
    self.shapetype == ShapeType::EDGE
  end

  def vertex?
    self.shapetype == ShapeType::VERTEX
  end

end
