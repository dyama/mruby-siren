#
# Array クラス拡張メソッド
# Shape 配列
#
class Array

  def to_curve
    Build.curve self
  end

  def to_polyline
    Build.polyline self
  end

  def to_polygon
    Build.polygon self
  end

  def to_wire(tol = 0.001)
    Build.wire self, tol
  end

  def to_loft
    
  end

  def to_revol

  end

  def to_shell
    Build.shell self
  end

  def to_solid
    Build.solid self.to_shell
  end

  def to_comp
    Build.compound self
  end

  def vertices;   self.map(&:vertices).flatten   end
  def edges;      self.map(&:edges).flatten      end
  def wires;      self.map(&:wires).flatten      end
  def faces;      self.map(&:faces).flatten      end
  def shells;     self.map(&:shells).flatten     end
  def solids;     self.map(&:solids).flatten     end
  def compsolids; self.map(&:compsolids).flatten end
  def compounds;  self.map(&:compounds).flatten  end

end

