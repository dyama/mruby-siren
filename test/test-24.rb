#!siren
# coding: utf-8

def test(&code)
  begin
    p code.call
  rescue => exc
    p exc
  end
end

test {
  point = [2, 2, 2]
  myline = Siren.line [1, 1, 1], [3, 3, 3]
  p myline.param point
  myline = Siren.line [0, 0, 0], [3, 3, 3]
  p myline.param point
}

test {
  include Siren
  line1 = line [0, 0, 0], [3, 3, 3]
  p line1.param [2, 2, 2]
  line2 = line [1, 1, 1], [3, 3, 3]
  p line2.param [2, 2, 2]
}
