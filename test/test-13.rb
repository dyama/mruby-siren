#!siren
# coding: utf-8

def test(&code)
  begin
    p code.call
  rescue => exc
    p exc
  end
end

include Siren

myface = plane [0, 0], Vec.z, Vec.x, 0, 3, 0, 3

es = []
es << line([1, 0], [1, 2])
es << line([1, 1], [3, 1])
es << line([2, 1], [2, 3])
es << line([2, 2], [0, 2])

# es.each_with_index do |e, i|
#   res = myface.split e
#   puts "#{i}: #{e.to_s}"
# end

p myface.split es.to_comp
