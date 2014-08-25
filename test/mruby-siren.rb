#!mruby

module ShapeType
  COMPOUND = 0
  COMPSOLID = 1
  SOLID = 2
  SHELL = 3
  FACE = 4
  WIRE = 5
  EDGE = 6
  VERTEX = 7
  SHAPE = 8

  def self.to_s(type)
    case type
    when ShapeType::COMPOUND
      return "COMPOUND"
    when ShapeType::COMPSOLID
      return "COMPSOLID"
    when ShapeType::SOLID
      return "SOLID"
    when ShapeType::SHELL
      return "SHELL"
    when ShapeType::FACE
      return "FACE"
    when ShapeType::WIRE
      return "WIRE"
    when ShapeType::EDGE
      return "EDGE"
    when ShapeType::VERTEX
      return "VERTEX"
    when ShapeType::SHAPE
      return "SHAPE"
    else
      return "UNKNOWN"
    end
  end

end

puts "--------------"
puts "mruby-siren.rb"
puts "--------------"

sp = Vec.new(5.0, 1.2, 3.8)
tp = Vec.new(8.0, 4.2, 3.8)
a = Build.line(sp, tp)

b = Build.vertex(1, 2, 3)

pts = []
pts.push Vec.new 1, 2, 3
pts.push Vec.new 3, 3, 3
pts.push Vec.new 2, 1, 3

c = Build.polyline pts

cmp = Build.compound([a, b, c])

BRepIO.save(cmp, "/tmp/hoge.brep")

cmp2 = BRepIO.load("/tmp/hoge.brep");
p cmp2.shapetype

ex = Exp.new cmp2, ShapeType::EDGE

while ex.more
  s = ex.current
  p "depth:" + ex.depth.to_s + " type:" + ShapeType::to_s(s.shapetype)
  ex.next()
end

#ex.to_a.each do |s|
#  p ShapeType::to_s(s.shapetype)
#end

