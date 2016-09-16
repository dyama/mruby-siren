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
test { Siren.sphere 1.0e-7}
test { Siren.sphere 0 }

# crash
test { Siren.sphere -1.0e-7 }

