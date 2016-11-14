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

module DxfPosition
  def x; self[10] || 0.0 end
  def y; self[20] || 0.0 end
  def z; self[30] || 0.0 end
  def x=(val); self[10] = val.to_f end
  def y=(val); self[20] = val.to_f end
  def z=(val); self[30] = val.to_f end
  def pos;    [self.x, self.y, self.z] end
  def pos=(*a)
    case a.size
    when 1
      if a.first.is_a?(Array)
        self.x = a.first[0]
        self.y = a.first[1]
        self.z = a.first[2]
      else
        raise ""
      end
    when 3
      self.x = a[0]
      self.y = a[1]
      self.z = a[2]
    else
      raise ""
    end
  end
end

class DxfEntity < Hash
  def initialize(ary = [])
    ary.each{ |n| self[n.keys.first] = n.values.first }
  end
  def type; self[0] end
  def layer; self[ 8] end
  def color; self[62] end
  def type=(val);  self[ 0] = val.to_s end
  def layer=(val); self[ 8] = val.to_s end
  def color=(val); self[62] = val.to_i end
end

class DxfPolyline < DxfEntity
  attr_accessor :vertices
  def initialize(ary = [])
    super ary.shift
    @vertices = ary.map{|n| DxfVertex.new n}
  end
end

class DxfVertex < DxfEntity
  include DxfPosition
end

class DxfText < DxfEntity
  include DxfPosition
  def height; self[40] || 1.0 end
  def angle;  self[50] || 0.0 end
  def itaric; self[51] || 0.0 end
  def style;  self[7] || "STANDARD" end
  def align;  self[72] || 0 end
  def valign; self[73] || 0 end
end

class Dxf

  include DxfRange

  attr_accessor :entities

  def initialize(path = nil)
    self.load(path) if path
  end

  def load(path)
    self.parse(File.read(path).lines)
  end

  def parse(lines = [])
    values = []
    lines.map(&:strip).each_slice(2) do |c, v|
      values.push({c.to_i => v})
    end
    values.extend(DxfRange)

    secs = values.range(->(a,b){a[0]=='SECTION'},->(a,b){a[0]=='ENDSEC'})
    # entsec = secs.select{|n|n[1][0]=='ENTITIES'}
    entsec = secs.first

    entsec.extend(DxfRange)
    ents = entsec.range(->(a,b){a[0]},->(a,b){b[0]})
    @entities = []
    con = false
    stk = []
    ents.each do |e|
      h = e.first
      if h[0] == 'TEXT'
        @entities << DxfText.new(e)
      elsif h[0] == 'POLYLINE'
        con = true
      elsif con && h[0] == 'SEQEND'
        con = false
        @entities << DxfPolyline.new(stk)
        stk.clear
      end
      stk << e if con
    end
  end

end

dir = "sample"

Dir.open(dir).each do |file|
  next if Dir.exist? file
  dxf = Dxf.new
  dxf.load("#{dir}/#{file}")
  pp dxf.entities.select{|n|n.class == DxfPolyline}.map{|n|n.vertices}
  # dxf.polylines.each do |t|
  #   pp t.vertices
  # end
  break
end

