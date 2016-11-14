#!siren
# coding: utf-8

module DxfRange
  def range(s, t)
    ary = []
    item = []
    flag = false
    (self.dup << self.last).each_cons(2) do |a, b|
      flag = true if !flag && s.call(a, b)
      if flag
        item.push(a)
        if t.call(a, b)
          ary.push(item) if item.size > 0
          flag = false
          item = []
        end
      end
    end
    ary.push(item) if item.size > 0
    ary
  end
end

class DxfValue < Array
  def initialize(code, value)
    self[0] = code.to_i
    self[1] = value
  end
  def code; self.first end
  def value; self.last end
  def code=(val); self[0] = val.to_i end
  def value=(val); self[1] = val end
  def eq?(code, value = nil)
    if value
      self.code == code && self.value == value
    else
      self.code == code
    end
  end
end

class DxfEntity < Hash
  def initialize(ary = [])
    ary.each{ |n| self[n.first] = n.last }
  end
  def layer; self[ 8] end
  def color; self[62] end
  def layer=(val); self[ 8] = val.to_s end
  def color=(val); self[62] = val.to_i end
end

class DxfPolyline < DxfEntity
  attr_accessor :vertices
  def initialize(ary = [])
    ary.extend(DxfRange)
    ply = ary.range(->(a,b){a.eq?0,'POLYLINE'},->(a,b){b.eq?0})
    super ply.first
    @vertices = ary.range(->(a,b){a.eq?0,'VERTEX'},->(a,b){b.eq?0}).map do |n|
      DxfEntity.new n
    end
  end
end

class DxfText < DxfEntity
  def pos; [self.x, self.y, self.z] end
  def x; self[10] || 0.0 end
  def y; self[20] || 0.0 end
  def z; self[30] || 0.0 end
  def height; self[40] || 1.0 end
  def angle; self[50] || 0.0 end
  def itaric; self[51] || 0.0 end
  def style; self[7] || "STANDARD" end
  def align; self[72] || 0 end
  def valign; self[73] || 0 end
end

class Dxf < Array

  include DxfRange

  def initialize(path = nil)
    self.load(path) if path
  end

  def load(path)
    self.parse(File.read(path).lines)
  end

  def parse(lines = [])
    lines.map(&:strip).each_slice(2) do |code, value|
      self.push(DxfValue.new(code, value))
    end
  end

  def entity_section
    r = self.range(->(a,b){a.eq?2,'ENTITIES'},->(a,b){a.eq?0,'ENDSEC'})
    if r.size > 0
      r.first
    else
      raise "DXF object has no entity section."
    end
  end

  def polylines
    ary = []
    ents = self.entity_section
    ents.extend(DxfRange)
    ents.range(->(a,b){a.eq?0,'POLYLINE'},->(a,b){b.eq?0,'SEQEND'}).each do |t|
      textobj = DxfPolyline.new(t)
      ary.push(textobj)
    end
    ary
  end

  def texts
    ary = []
    ents = self.entity_section
    ents.extend(DxfRange)
    ents.range(->(a,b){a.eq?0,'TEXT'},->(a,b){b.eq?0}).each do |t|
      textobj = DxfText.new(t)
      ary.push(textobj)
    end
    ary
  end

end

dir = "sample"

Dir.open(dir).each do |file|
  next if Dir.exist? file
  dxf = Dxf.new
  dxf.load("#{dir}/#{file}")
  dxf.polylines.each do |t|
    pp t.vertices
  end
end

