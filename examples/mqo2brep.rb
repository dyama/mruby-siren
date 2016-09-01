#!/usr/bin/env siren
# vim:fileencoding=utf-8

class MqObject
  attr_accessor :vertex, :face
  def build
    faces = face.map do |s|
      /V\(([^\)]+)\)/ =~ s
      nos = $1.split(/  */).map(&:to_i)
      if nos.last != nos.first
        nos << nos.first
      end
      pts = nos.map{|p| @vertex[p]}
      begin
        Siren.polygon pts, true
      rescue
        nil
      end
    end
    faces.select{|f| f != nil}
  end
end

models = []

ARGV.each do |path|
  File.open(path, "r") do |f|
    while line = f.gets
      line.gsub!(/^\s+/, "")
      if /^Object "([^"]*)"/ =~ line
        objname = $1 
        curr = MqObject.new
        # puts "#{objname} found."

        while line = f.gets
          break if /^vertex/ =~ line.gsub(/^\s+/,"")
        end
        curr.vertex = Array.new
        while line = f.gets
          break if /^}/ =~ line.gsub!(/^\s+/,"")
          curr.vertex.push(line.split(/\s/).select{|val| val != nil }.map {|val| val.to_f })
        end

        while line = f.gets
          break if /^face/ =~ line.gsub(/^\s+/,"")
        end
        curr.face = Array.new
        while line = f.gets
          break if /^}/ =~ line.gsub!(/^\s+/,"")
          curr.face.push(line.gsub(/  +/, " ").gsub(/\n/,""))
        end

        models.push curr
      end
    end
  end
end

if models.size > 0
  fs = []
  models.each do |m|
    fs += m.build
  end

  Siren.save_brep Siren.compound(fs), "mqo.brep"
  puts "done"
end

