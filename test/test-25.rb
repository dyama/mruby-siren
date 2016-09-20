#!siren
# coding: utf-8

def test(&code)
  begin
    p code.call
  rescue => exc
    p exc
  end
end

# ok
test { Siren.plane [0, 0, 0], [0, 0, 1], [0, 1, 0], -1, 1, -1, 1 }
test { Siren.plane [2, 3, 4], [0, 1, 1], [1, 1, 0], -1, 1, -1, 1 }

# crash
test { Siren.plane [0, 0, 0], [0, 0, 1], [0, 0, 2], -1, 1, -1, 1 }
