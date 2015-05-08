#!/usr/bin/env siren
# coding: utf-8

# CSV offset table parser
def get_table(ofsfile)
  t = {}
  ci = []
  File::open(ofsfile, "r") do |f|
    f.each do |ln|
      ar = ln.chomp.split(",")
      if ar.first == "" # Colum header
        ar.slice(1..-1).each do |ord|
          t[ord.to_f] = {}
          ci.push ord.to_f
        end
      else
        ar.slice(1..-1).each_with_index do |val, i|
          t[ci[i]][ar.first.to_f] = val.to_f
        end
      end
    end
  end
  return t
end

def make_shell(tbl, lpp)
  cvs = []
  tbl.each_pair do |k, v|
    pts = []
    x = k * lpp * 0.1
    v.each_pair do |z, y|
      pts.push Vec::new(x, y, z)
    end
    #cvs.push Build::curve(pts)
    cvs.push Build::polyline(pts)
  end
  cvs.map!{|e| Build::wire [e] }
  Offset::loft(cvs, false, false, true)
end

def get_area(tbl, lpp)
  ar = tbl.to_a
  aex = ar.first.first * lpp * 0.1
  fex = ar.last.first  * lpp * 0.1
  dmin = ar.first.last.to_a.first.first
  dmax = ar.first.last.to_a.last.first
  [aex, fex, dmin, dmax]
end

def make_top(tbl, lpp)
  pts = []
  aex, fex, dmin, dmax = get_area(tbl, lpp)
  pts.push Vec::new(aex, 0, dmax)
  tbl.each_pair do |k, v|
    gnl = v.to_a.last
    pts.push Vec::new(k * lpp * 0.1, gnl.last, gnl.first)
  end
  pts.push Vec::new(fex, 0, dmax)
  Build::polygon pts
end

def make_center(tbl, lpp)
  aex, fex, dmin, dmax = get_area(tbl, lpp)
  Build::polygon [
    Vec::new(aex, 0, dmin),
    Vec::new(aex, 0, dmax),
    Vec::new(fex, 0, dmax),
    Vec::new(fex, 0, dmin),
  ]
end

def make_section(xpos, curve)


end

lpp = 217.0
table = get_table(ARGV[0])
top    = make_top(table, lpp)
center = make_center(table, lpp)
shell  = make_shell(table, lpp)

# 以下、表示
world = World.new `echo $DISPLAY`.chomp
cam = Camera.new world, X11.test
ss = Skin.new shell
ss.color = ColorName::RED
world.add ss
st = Skin.new top
st.color = ColorName::BLUE1
world.add st
sc = Skin.new center
sc.color = ColorName::GREEN
world.add sc
# 視点・視野設定
cam.proj = OrientType::XnegYnegZpos
cam.fitz
cam.fit
# Enter が押されたら終了
STDIN.gets

