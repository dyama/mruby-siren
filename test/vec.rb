#!siren
# coding: utf-8
# Test script for Siren::Vec class.

include Siren

class Test4VecClass < MTest::Unit::TestCase

  def test_constant
    assert [0, 0, 0], Vec::o.to_a
    assert [1, 0, 0], Vec::x.to_a
    assert [0, 1, 0], Vec::y.to_a
    assert [0, 0, 1], Vec::z.to_a
    assert [1, 1, 0], Vec::xy.to_a
    assert [1, 0, 1], Vec::xz.to_a
    assert [1, 1, 0], Vec::yx.to_a
    assert [0, 1, 1], Vec::yz.to_a
    assert [1, 0, 1], Vec::zx.to_a
    assert [0, 1, 1], Vec::zy.to_a
    assert [1, 1, 1], Vec::xyz.to_a
    assert [0, 0, 0], Vec::zero.to_a
    assert [1, 0, 0], Vec::xdir.to_a
    assert [0, 1, 0], Vec::ydir.to_a
    assert [0, 0, 1], Vec::zdir.to_a
  end

  def test_initialize
    assert_equal [0, 0, 0], Vec.new.to_a
    assert_equal [1, 0, 0], Vec.new(1).to_a
    assert_equal [1, 1, 0], Vec.new(1, 1).to_a
    assert_equal [1, 1, 1], Vec.new(1, 1, 1).to_a
    assert_equal [0, 0, 0], Vec.new([]).to_a
    assert_equal [1, 0, 0], Vec.new([1]).to_a
    assert_equal [1, 1, 0], Vec.new([1, 1]).to_a
    assert_equal [1, 1, 1], Vec.new([1, 1, 1]).to_a
  end

  def test_operater
    assert_equal [-1, 0, 0],      (-Vec.new(1, 0, 0)).to_a
    assert_equal [1, 1, 2],       (Vec.new(1, 1, 1) + Vec.new(0, 0, 1)).to_a
    assert_equal [1, 1, 0],       (Vec.new(1, 1, 1) - Vec.new(0, 0, 1)).to_a
    assert_equal [2, 2, 2],       (Vec.new(1, 1, 1) * 2).to_a
    assert_equal [-10, 0, 0],     (-Vec::xdir * 10).to_a
    assert_equal [0.5, 0.5, 0.5], (Vec.new(1, 1, 1) / 2).to_a
    assert_true  Vec.new(1, 0, 0) == Vec.new(1, 0, 0)
    assert_false Vec.new(1, 1, 0) == Vec.new(1, 0, 0)
    assert_false Vec.new(1, 0, 0) != Vec.new(1, 0, 0)
    assert_true  Vec.new(1, 1, 0) != Vec.new(1, 0, 0)
  end

  def test_operater_2d
    assert_equal [-1, 0, 0],    (-Vec.new(1, 0)).to_a
    assert_equal [1, 2, 0],     (Vec.new(1, 1) + Vec.new(0, 1)).to_a
    assert_equal [1, 0, 0],     (Vec.new(1, 1) - Vec.new(0, 1)).to_a
    assert_equal [2, 2, 0],     (Vec.new(1, 1) * 2).to_a
    assert_equal [0.5, 0.5, 0], (Vec.new(1, 1) / 2).to_a
    assert_true  Vec.new(1, 0, 0) == Vec.new(1, 0)
    assert_false Vec.new(1, 1, 0) == Vec.new(1, 0)
    assert_false Vec.new(1, 0, 0) != Vec.new(1, 0)
    assert_true  Vec.new(1, 1, 0) != Vec.new(1, 0)
  end

  def test_xyz
    assert_equal 1, Vec.new(1, 2, 3).x
    assert_equal 2, Vec.new(1, 2, 3).y
    assert_equal 3, Vec.new(1, 2, 3).z
    vec = Vec.new(0, 0, 0)
    vec.x = 1
    assert_equal 1, vec.x
    vec.y = 2
    assert_equal 2, vec.y
    vec.z = 3
    assert_equal 3, vec.z
    assert_equal [1, 2, 3], vec.to_a
  end

  def test_ext_array
    assert_equal Vec.new(0, 0, 0), [].to_v
    assert_equal Vec.new(0, 0, 0), [0].to_v
    assert_equal Vec.new(0, 1, 0), [0, 1].to_v
    assert_equal Vec.new(0, 1, 2), [0, 1, 2].to_v
    assert_equal Vec.new(0, 1, 2), [0, 1, 2, 3].to_v
    assert_equal 0, [].x
    assert_equal 0, [].y
    assert_equal 0, [].z
    assert_equal 1, [1, 0, 0].x
    assert_equal 1, [0, 1, 0].y
    assert_equal 1, [0, 0, 1].z
    ary = []
    ary.x = 1
    assert_equal 1, ary.x
    ary.y = 2
    assert_equal 2, ary.y
    ary.z = 3
    assert_equal 3, ary.z
    assert_equal [1, 2, 3], ary
  end

  def test_method
    assert_equal [1, 0, 0], Vec.new(100, 0, 0).normal.to_a
    # assert_equal [Math.sqrt(2) / 2, Math.sqrt(2) / 2, 0], Vec.new(100, 100, 0).normal.to_a
  end

end


MTest::Unit.new.run
