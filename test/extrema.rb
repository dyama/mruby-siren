#!/usr/bin/siren
# coding: utf-8

# Test for extrema (get nearest point)

include Siren

a = infline [], Vec.x
b = line [2, 0, 5], [2, 10, 5]
p a.extrema b
