#
# Solid クラス拡張メソッド
#
class Siren::Solid

  def area
    self.shells.inject { |e| e.area }
  end

end
