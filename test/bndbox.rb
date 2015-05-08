#!/usr/bin/env siren
# coding: utf-8

a = Prim.box [10, 5, 3]

bb = a.bndbox

puts "x"
p bb.min.x
p bb.max.x

puts "y"
p bb.min.y
p bb.max.y

puts "z"
p bb.min.z
p bb.max.z
