#!mruby
# coding: utf-8

module DxfPosition
  def x; self[10] || 0.0 end
  def y; self[20] || 0.0 end
  def z; self[30] || 0.0 end
  def x=(val); self[10] = val.to_f end
  def y=(val); self[20] = val.to_f end
  def z=(val); self[30] = val.to_f end
  def xyz; [self.x, self.y, self.z] end
  def xyz=(ary); self.x, self.y, self.z = ary end
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
  def serial
    s = ''
    s += {  0 => self.type}.serial
    s += {  5 => self.handle}.serial
    s += {100 => 'AcDbEntity'}.serial if @scm
    s += {  8 => self.layer}.serial
    s += { 62 => self.color}.serial
    # s += {  6 => self.style}.serial
    s += { 48 => self[48]}.serial
    s
  end
end

class DxfLine < DxfEntity
  include DxfPosition
  def style; self[6] end
  def serial
    s = super
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
  #   DXF          CAD APP       備考
  #   -----------  ------------- --------------------------------
  # 1 POLYLINE     3D ポリライン 円弧はサポートしない(VERTEXのみ)
  # 2 POLYLINE     ポリライン    DXF上最もシンプルな定義
  # 3 LWPOLYLINE   ポリライン    R14以降対応。2Dに特化。
  #
  # CADAPPで2を読み込むと表現上はポリラインとなる。
  # CADAPPで通常のポリラインを作成する場合、3になる。
  # 1と2のPOLYLINEはサブクラスマーカー(AcDb3dPolyline/AcDb2dPolyline)で
  # 区別されてそう。
  attr_accessor :vertices
  def initialize(ary = [])
    super ary.shift
    @seqend = ary.pop
    @vertices = ary.map{|n| DxfVertex.new n}
  end
  def style; self[6] end
  def serial
    s = super
    s += {100 => 'AcDb3dPolyline'}.serial if @scm
    s += { 66 => self[66] || 0}.serial
    s += {
      10 => 0.0,
      20 => 0.0,
      30 => 0.0,
    }.serial
    s += { 39 => self[39]}.serial
    s += { 70 => self[70] || 0}.serial
    s += { 40 => self[40]}.serial if self[40] != 0.0
    s += { 41 => self[41]}.serial if self[41] != 0.0
    s += { 70 => self[70]}.serial if self[70] != 0
    s += { 71 => self[71]}.serial if self[71] != 0
    s += { 72 => self[72]}.serial if self[72] != 0
    s += { 73 => self[73]}.serial if self[73] != 0
    s += { 74 => self[74]}.serial if self[74] != 0
    s += { 75 => self[75]}.serial if self[75] != 0
    @vertices.each do |v|
      s += v.serial
    end
    if @scm
      @seqend.each do |n|
        s += n.to_h.serial
      end
    else
      s += "  0\nSEQEND\n"
    end
    s
  end
end

class DxfVertex < DxfEntity
  include DxfPosition
  def serial
    s = super
    s += {100 => 'AcDbVertex'}.serial if @scm
    s += {100 => 'AcDb3dPolylineVertex'}.serial if @scm
    s += {
      10 => self.x,
      20 => self.y,
      30 => self.z,
    }.serial
    s += {
      40 => self[40],
      41 => self[41],
      42 => self[42],
      70 => self[70],
      50 => self[50],
      71 => self[71],
      72 => self[72],
      73 => self[73],
      74 => self[74],
      91 => self[91],
    }.serial if false
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
    s = super
    s += {100 => 'AcDbText'}.serial if @scm
    s += { 39 => self.thick}.serial  if self.thick != 0.0
    s += {
      10 => self.x,
      20 => self.y,
      30 => self.z,
      40 => self.height,
       1 => self.value,
    }.serial
    s += { 50 => self.angle}.serial if self.angle != 0.0
    s += { 41 => self.xfact}.serial  if self.xfact != 0.0
    s += { 51 => self.italic}.serial if self.italic != 0.0
    s += {  7 => self.style}.serial  if self.style != 'STANDARD'
    s += { 71 => self.mirror}.serial if self.mirror != 0
    s += { 72 => self.align}.serial if self.align != 0
    s += {
      11 => self[11] || 0.0,
      21 => self[21] || 0.0,
      31 => self[31] || 0.0,
    }.serial if self.align != 0 || self.valign != 0
    s += {100 => 'AcDbText'}.serial if @scm
    s += { 73 => self.valign}.serial if self.valign != 0
    s
  end
end

class RanCon
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

  attr_accessor :es

  def initialize(path = nil)
    @src = []
    self.parse(path) if path
  end

  def parse(path)

    @header = []
    @classes= []
    @tables = []
    @blocks = []
    @ents   = []
    @objs   = []

    cnd_header = RanCon.new(->(c){c[2]=='HEADER'},  ->(c){c[0]=='ENDSEC'})
    cnd_classes= RanCon.new(->(c){c[2]=='CLASSES'}, ->(c){c[0]=='ENDSEC'})
    cnd_tables = RanCon.new(->(c){c[2]=='TABLES'},  ->(c){c[0]=='ENDSEC'})
    cnd_blocks = RanCon.new(->(c){c[2]=='BLOCKS'},  ->(c){c[0]=='ENDSEC'})
    cnd_ents   = RanCon.new(->(c){c[2]=='ENTITIES'},->(c){c[0]=='ENDSEC'})
    cnd_objs   = RanCon.new(->(c){c[2]=='OBJECTS'}, ->(c){c[0]=='ENDSEC'})

    File.open(path, "r") do |f|
      while code = f.gets
        break unless code
        code = code.to_i
        val = f.gets.strip
        if cnd_header.test({code => val})
          @header << [code, val]
        elsif cnd_classes.test({code => val})
          @classes << [code, val]
        elsif cnd_tables.test({code => val})
          @tables << [code, val]
        elsif cnd_blocks.test({code => val})
          @blocks << [code, val]
        elsif cnd_ents.test({code => val})
          @ents << [code, val]
        elsif cnd_objs.test({code => val})
          @objs << [code, val]
        end
      end
    end

    con = false
    stk = []
    @es = []

    Enumerator.new { |y|
      ee = []
      @ents.each do |e|
        if e.first == 0
          y << ee.dup if ee.size > 0 && ee.first.first == 0
          ee.clear
        end
        ee << e
      end
      y << ee.dup if ee.size > 0 && ee.first.last != 'ENDSEC'
    }.each { |e|
      case e[0][1]
      when 'TEXT'
        @es << DxfText.new(e)
      when 'LINE'
        @es << DxfLine.new(e)
      when 'POLYLINE'
        con = true
      end
      if con
        stk << e
        if e[0][1] == 'SEQEND'
          @es << DxfPolyline.new(stk)
          con = false
          stk.clear
        end
      end
    }

  end

  def serial
    Enumerator.new do |y|
      putsec = ->(src) {
        if src && src.size > 0
          y << {0 => 'SECTION'}.serial
          src.each do |a|
            y << a.to_h.serial
          end
        end
      }
      putsec.call(@header)
      putsec.call(@classes)
      putsec.call(@tables)
      putsec.call(@blocks)
      if false
      putsec.call(@ents)
      else
        y << {0 => 'SECTION'}.serial
        y << {2 => 'ENTITIES'}.serial
        @es.each do |e|
          y << e.serial
        end
        y << {0 => 'ENDSEC'}.serial
      end
      putsec.call(@objs)
      y << {0 => 'EOF'}.serial
    end
  end

end

# dxf = DxfDocument.new("/tmp/dxf/2013.dxf")
# File.open("/tmp/dxf/2013-2.dxf", "w") do |f|
#   dxf.serial.each do |s|
#     f.write(s)
#   end
# end

dxf = DxfDocument.new("/tmp/dxf/2.dxf")
File.open("/tmp/dxf/2-2.dxf", "w") do |f|
  dxf.serial.each do |s|
    f.write(s)
  end
end
