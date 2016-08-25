#!/usr/bin/env ruby
# coding: utf-8

# 最小二乗法による直線 y = a * x + b の式の算出

s1 = [[32.0,  24.0],
     [131.0,  62.0],
     [159.0, 110.0],
     [245.0, 146.0]]
s2 = [[ 0.0,   0.0],
     [  0.0,  10.0],
     [  0.0,  20.0],
     [  0.0,  30.0]]
s3 = [[  0.0,  0.0],
     [  10.0,  0.0],
     [  20.0,  0.0],
     [  30.0,  0.0]]
s = s1

def s.sum(&b)
  self.inject(0.0) do |t, pnt|
    t + b.call(pnt[0], pnt[1])
  end
end

n = s.size.to_f
a = (n * s.sum{|x,y|x*y} - s.sum{|x,y|x} * s.sum{|x,y|y}) /
  (n * s.sum{|x,y|x**2} - (s.sum{|x,y|x})**2)
b = (s.sum{|x,y|x**2} * s.sum{|x,y|y} - s.sum{|x,y|x*y} * s.sum{|x,y|x}) /
  (n * s.sum{|x,y|x**2} - (s.sum{|x,y|x})**2)

puts "a: #{a}"
puts "b: #{b}"

line = nil
if a == 0 && b == 0
  puts "horizontal"
  line = Build.infline [0.0, s[0].y], Vec::xdir
elsif a.nan? && b.nan?
  puts "vertical"
  line = Build.infline [s[0].x, 0.0], Vec::ydir
else
  p1 = [0.0, b]
  p2 = [100.0, a*100.0+b]
  dir = p2 - p1
  line = Build.infline p1, dir
end

ps = s.map {|pt| Build.vertex pt}
ps << line
comp = Build.compound ps
BRepIO.save comp, "sample-line.brep"

