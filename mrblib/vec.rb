#
# Vec クラスのための Array クラス拡張メソッド
#
class Array
  def to_v
    if size == 0
      Vec::new 0.0, 0.0, 0.0
    else
      x = 0.0, y = 0.0, z = 0.0
      if size > 0 then x = self[0].to_f end
      if size > 1 then y = self[1].to_f end
      if size > 2 then z = self[2].to_f end
      Vec::new x, y, z
    end
  end
end

