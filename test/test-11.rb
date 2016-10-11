#!siren
# coding: utf-8

def test(&code)
  begin
    p code.call
  rescue => exc
    p exc
  end
end

Siren.wedge
Siren.wedge 10, 10, 10, 0, 10, 0, 10
