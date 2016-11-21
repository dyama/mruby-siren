#!siren

include Siren

$f = plane Vec.o, Vec.x, Vec.y, 0, 3, 0, 3

class Test4FaceSplitter < MTest::Unit::TestCase

  def test1
    es = []
    es << line([1, 0], [1, 2])
    es << line([1, 1], [3, 1])
    es << line([2, 1], [2, 3])
    es << line([2, 2], [0, 2])
    w = wire es, 0.1
    p $f.split(w)
  end

  def test2
    es = []
    es << line([1, 0], [1, 1])
    es << line([1, 1], [1, 2])
    es << line([1, 1], [2, 1])
    es << line([2, 1], [3, 1])
    es << line([2, 1], [2, 2])
    es << line([2, 2], [2, 3])
    es << line([2, 2], [1, 2])
    es << line([1, 2], [0, 2])
    w = wire es, 0.1
    p $f.split(w)
  end

  def test3
    w = polyline [[1, 1], [2, 1], [2, 2], [1, 2], [1, 1]]
    p $f.split(w)
  end

  def test4
    w = line([0, 1], [3, 3])
    p $f.split(w)
  end

end

MTest::Unit.new.run

