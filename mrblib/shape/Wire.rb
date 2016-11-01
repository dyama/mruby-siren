#
# Wire クラス拡張メソッド
#
class Siren::Wire

  def length
    self.edges.inject { |e| e.length }
  end

end
