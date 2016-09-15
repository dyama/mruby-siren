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
test { Siren.curve [[], [1]] }
test { Siren.curve [[], [1], []] }

# crash
test { Siren.curve [[], []] }
test { Siren.curve [[1], [], []] }
test { Siren.curve [[], [1], [1], []] }

