#!siren
# coding: utf-8

# respond_to?(:load) || def load path
#   eval File.read(path)
# end
# load "lib.rb"

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

class Hash
  def serial
    s = ''
    self.each do |key, val|
      next unless val
      s += sprintf("% 3d\n", key)
      if val.is_a? Float
        s += sprintf "%0.0f\n", val
      else
        s += "#{val}\n"
      end
    end
    s
  end
end

module DxfSerializeSection
  def serial
    ss = ''
    self.each do |n|
      ss += n.serial
    end
    ss
  end
end

class DxfEntity < Hash
  def initialize(ary = [])
    @scm = false
    ary.each do |n|
      key = n.keys.first
      val = n.values.first
      if key == 100
        @scm = true
      else
        self[key] = val
      end
    end
  end
  def type;   self[ 0] end
  def handle; self[ 5] end
  def layer;  self[ 8] end
  def color;  self[62] end
  def type=(val);  self[ 0] = val.to_s end
  def layer=(val); self[ 8] = val.to_s end
  def color=(val); self[62] = val.to_i end
end

class DxfLine < DxfEntity
  include DxfPosition
  def style; self[6] end
  def serial
    s = ''
    s += {  0 => 'LINE'}.serial
    s += {  5 => self.handle}.serial
    s += {100 => 'AcDbEntity'}.serial if @scm
    s += {  8 => self.layer}.serial
    s += { 62 => self.color}.serial
    s += {100 => 'AcDbLine'}.serial if @scm
    s += {  6 => self.style}.serial
    s += { 10 => self.x}.serial
    s += { 20 => self.y}.serial
    s += { 30 => self.z}.serial
    s += { 11 => self[11] || 0.0}.serial
    s += { 21 => self[21] || 0.0}.serial
    s += { 31 => self[31] || 0.0}.serial
    s
  end
end

class DxfPolyline < DxfEntity
  attr_accessor :vertices
  def initialize(ary = [])
    super ary.shift
    @seqend = ary.pop
    @vertices = ary.map{|n| DxfVertex.new n}
  end
  def style; self[6] end
  def serial
    s = ''
    s += {  0 => 'POLYLINE'}.serial
    s += {  5 => self.handle}.serial
    s += { 62 => self.color}.serial
    s += {  6 => self.style}.serial
    s += { 48 => self[48]}.serial
    s += {  8 => self.layer}.serial
    s += { 66 => self[66] || 0}.serial
    s += { 70 => self[70] || 0}.serial
    s += {
      10 => 0.0,
      20 => 0.0,
      30 => 0.0,
    }.serial
    @vertices.each do |v|
      s += v.serial
    end
    @seqend.each do |n|
      s += n.serial
    end
    s
  end
end

class DxfVertex < DxfEntity
  include DxfPosition
  def serial
    s = ''
    s += {  0 => 'VERTEX'}.serial
    s += {  5 => self.handle}.serial
    s += {  6 => self[6]}.serial
    s += { 48 => self[48]}.serial
    s += {  8 => self.layer}.serial
    s += { 62 => self[62]}.serial
    s += {
      10 => self.x,
      20 => self.y,
      30 => self.z,
    }.serial
    s
  end
end

class DxfText < DxfEntity
  include DxfPosition
  def value;  self[1] || ' ' end
  def height; self[40] || 1.0 end
  def angle;  self[50] || 0.0 end
  def italic; self[51] || 0.0 end
  def style;  self[7] || 'STANDARD' end
  def mirror; self[71] || 0 end
  def align;  self[72] || 0 end
  def valign; self[73] || 0 end
  def thick;  self[39] || 0.0 end
  def xfact;  self[41] || 0.0 end
  def serial
    s = ''
    s += {  0 => 'TEXT'}.serial
    s += {  5 => self.handle}.serial
    s += {100 => 'AcDbEntity'}.serial if @scm
    s += {  8 => self.layer}.serial
    s += { 62 => self.color}.serial
    s += {100 => 'AcDbText'}.serial if @scm
    s += {  1 => self.value}.serial
    s += { 10 => self.x}.serial
    s += { 20 => self.y}.serial
    s += { 30 => self.z}.serial
    s += { 40 => self.height}.serial
    s += { 51 => self.italic}.serial if self.italic != 0.0
    s += { 41 => self.xfact}.serial  if self.xfact != 0.0
    s += {  7 => self.style}.serial  if self.style != 'STANDARD'
    s += { 39 => self.thick}.serial  if self.thick != 0.0
    s += { 71 => self.mirror}.serial if self.mirror != 0
    if self.align != 0
      s += {
        11 => self[11] || 0.0,
        21 => self[21] || 0.0,
        31 => self[31] || 0.0,
        72 => self.align,
      }.serial
    end
    s += { 73 => self.valign}.serial
    s += {100 => 'AcDbText'}.serial
    s
  end
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
    # {key: value} のハッシュ列に変換
    values = []
    lines.map(&:strip).each_slice(2) do |c, v|
      values.push({c.to_i => v})
    end
    values.extend(DxfRange)

    # セクション分割
    secs = values.range(->(a,b){a[0]=='SECTION'},->(a,b){a[0]=='ENDSEC'})

    # HEADER セクション
    @header = secs.select{|n| n[1][2]=='HEADER' }&.first

    # CLASSES セクション
    @classes = secs.select{|n| n[1][2]=='CLASSES' }&.first

    # TABLES セクション
    @tables = secs.select{|n| n[1][2]=='TABLES' }&.first

    # BLOCKS セクション
    @blocks = secs.select{|n| n[1][2]=='BLOCKS' }&.first

    # ENTITIES セクション
    entsec = secs.select{|n| n[1][2]=='ENTITIES' }&.first
    if entsec
      entsec.extend(DxfRange)
      ents = entsec.range(->(a,b){a[0]},->(a,b){b[0]})
      @entities = []
      con = false
      stk = []
      ents.each do |e|
        h = e.first
        if h[0] == 'TEXT'
          @entities << DxfText.new(e)
        elsif h[0] == 'LINE'
          @entities << DxfLine.new(e)
        elsif h[0] == 'POLYLINE'
          con = true
        elsif con && h[0] == 'SEQEND'
          stk << e
          @entities << DxfPolyline.new(stk)
          con = false
          stk.clear
        end
        stk << e if con
      end
    end

    # OBJECTS セクション
    @objects = secs.select{|n| n[1][2]=='OBJECTS' }&.first

    # THUMBNAILIMAGE セクション
    @thumbnailimage = secs.select{|n| n[1][2]=='THUMBNAILIMAGE' }&.first
  end

  def serial
    s = ''
    @header&.extend(DxfSerializeSection)
    @classes&.extend(DxfSerializeSection)
    @tables&.extend(DxfSerializeSection)
    @blocks&.extend(DxfSerializeSection)
    @objects&.extend(DxfSerializeSection)
    @thumbnailimage&.extend(DxfSerializeSection)
    s += @header&.serial || ''
    s += @classes&.serial || ''
    s += @tables&.serial || ''
    s += @blocks&.serial || ''
    s += {0 => 'SECTION', 2 => 'ENTITIES'}.serial
    @entities.each do |ent|
      s += ent.serial
    end
    s += {0 => 'ENDSEC'}.serial
    s += @objects&.serial || ''
    s += @thumbnailimage&.serial || ''
    s += {0 => 'EOF'}.serial
    s
  end

end

# dxf = Dxf.new "/tmp/dxf/2.dxf"
# s = dxf.serial
# File.open("/tmp/2-2.dxf", "w") do |f|
#   f.write s
# end

dir = "sample"
# dir = "/tmp/dxf"

Dir.open(dir).each do |file|
  next if Dir.exist? file
  dxf = Dxf.new
  dxf.load("#{dir}/#{file}")
  s = dxf.serial
  File.open("/tmp/dxf/a/#{file}", "w") do |f|
    f.write s
  end
end

