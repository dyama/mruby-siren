#
# Shell クラス拡張メソッド
#
class Siren::Shell

  def area
    self.faces.inject { |e| e.area }
  end

end
