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
test { Siren.box [1, 2, 3] }
test { Siren.box [1, 2, -3] }
test { Siren.box [-1, -2, -3] }
test { Siren.box [Float::NAN, 1, 1] }

# crash
test { Siren.box [1, "foobar", 1] }
test { Siren.box [1, 2, nil] }

