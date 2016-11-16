#!mruby
# coding: utf-8

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
      key, val = n.to_a
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

class RangeCondition
  def initialize(s, t)
    @s = s
    @t = t
    @f = @s ? -1 : 0
  end
  def init
    @f = @s ? -1 : 0
  end
  def test(*args)
    case @f
    when -1 # yet
      if @s.call(*args)
        @f = 0
        true
      else
        false
      end
    when 0 # now
      if @t && @t.call(*args)
        @f = 1
      end
      true
    else # done
      false
    end
  end
end

class DxfDocument

  def initialize(path = nil)
    self.load(path) if path
  end

  def parse(path)

    @src = []
    @header = []
    @clss   = []
    @tables = []
    @blocks = []
    @ents   = []
    @objs   = []
    @thumb  = []

    cnd_header = RangeCondition.new(->(c){c[2]=='HEADER'},  ->(c){c[0]=='ENDSEC'})
    cnd_clss   = RangeCondition.new(->(c){c[2]=='CLASSES'}, ->(c){c[0]=='ENDSEC'})
    cnd_tables = RangeCondition.new(->(c){c[2]=='TABLES'},  ->(c){c[0]=='ENDSEC'})
    cnd_blocks = RangeCondition.new(->(c){c[2]=='BLOCKS'},  ->(c){c[0]=='ENDSEC'})
    cnd_ents   = RangeCondition.new(->(c){c[2]=='ENTITIES'},->(c){c[0]=='ENDSEC'})
    cnd_objs   = RangeCondition.new(->(c){c[2]=='OBJECTS'}, ->(c){c[0]=='ENDSEC'})
    cnd_thumb  = RangeCondition.new(->(c){c[2]=='THUMBNAILIMAGE'},->(c){c[0]=='ENDSEC'})

    File.open(path, "r") do |f|
      while code = f.gets
        break unless code
        code = code.to_i
        val = f.gets.strip
        @src << [code, val]
        # @header << [code, val] if cnd_header.test({code => val})
        # @clss   << [code, val] if cnd_clss.test({code => val})
        # @tables << [code, val] if cnd_tables.test({code => val})
        # @blocks << [code, val] if cnd_blocks.test({code => val})
        # @ents   << [code, val] if cnd_ents.test({code => val})
        # @objs   << [code, val] if cnd_objs.test({code => val})
        # @thumb  << [code, val] if cnd_thumb.test({code => val})
      end
    end

    # con = false
    # stk = []
    # @es = []

    # Enumerator.new { |y|
    #   ee = []
    #   @ents.each do |e|
    #     if e.first == 0
    #       y << ee.dup if ee.size > 0 && ee.first.first == 0
    #       ee.clear
    #     end
    #     ee << e
    #   end
    #   y << ee.dup if ee.size > 0 && ee.first.last != 'ENDSEC'
    # }.each { |e|
    #   case e[0][1]
    #   when 'TEXT'
    #     @es << DxfText.new(e)
    #   when 'POLYLINE'
    #     con = true
    #   end
    #   if con
    #     stk << e
    #     if e[0][1] == 'SEQEND'
    #       @es << DxfPolyline.new(stk)
    #       con = false
    #       stk.clear
    #     end
    #   end
    # }

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

#dxf = DxfDocument.new("/tmp/dxf/s/PR_SUPP_IB.1.dxf")
dxf = DxfDocument.new
dxf.parse("/tmp/dxf/1.dxf")
# File.open("/tmp/dxf/s/PR_SUPP_IB.1-2.dxf", "w") do |f|
#   f.write(dxf.serial)
# end

# dir = "sample"
# # dir = "/tmp/dxf"
# Dir.open(dir).each do |file|
#   next if Dir.exist? file
#   dxf = DxfDocument.new
#   dxf.load("#{dir}/#{file}")
#   s = dxf.serial
#   File.open("/tmp/dxf/a/#{file}", "w") do |f|
#     f.write s
#   end
# end

