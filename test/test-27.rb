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
  a = Siren.box
  b = Siren.box
  a.translate! [0.5]
  a.fuse(b).volume
}

test {
  a = Siren.box
  b = Siren.box
  a.translate! [0.5]
  a.cut(b).volume
}

