#
# Array クラス拡張メソッド
# Shape 配列
#
class Array

  def to_curve
    Siren.curve self
  end

  def to_polyline
    Siren.polyline self
  end

  def to_polygon
    Siren.polygon self
  end

  def to_wire(tol = 0.001)
    Siren.wire self, tol
  end

  def to_loft
    raise NotImplementedError
  end

  def to_revol
    raise NotImplementedError
  end

  def to_shell
    Siren.shell self
  end

  def to_solid
    Siren.solid self.to_shell
  end

  def to_comp
    Siren.compound self
  end

  def vertices;   self.map(&:vertices).flatten   end
  def edges;      self.map(&:edges).flatten      end
  def wires;      self.map(&:wires).flatten      end
  def faces;      self.map(&:faces).flatten      end
  def shells;     self.map(&:shells).flatten     end
  def solids;     self.map(&:solids).flatten     end
  def compsolids; self.map(&:compsolids).flatten end
  def compounds;  self.map(&:compounds).flatten  end

  def bndbox
    raise NotImplementedError
  end

end

