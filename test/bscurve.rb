#!/usr/bin/env siren
# coding: utf-8

include Siren

degree = 2
# knots = [0, 0, 0, 1, 2, 2, 2]
# use commpressed knot array
knots = [0.0, 1.0, 2.0]
mults = [3, 1, 3]
poles = [[10, 0, 7], [7, 0, 7], [3, 0, 8], [0, 0, 7]]
weights = [1.0, 1.2, 1.0, 1.0]

if true
  e = bscurve degree, knots, mults, poles, weights, 0.1, 1.2
  p e
  p e.curve.class
  p e.curve.degree
  p e.curve.knots
  p e.curve.mults
  p e.curve.poles
  p e.curve.weights
else
  c = BSCurve.new degree, knots, mults, poles, weights
  p c
  p c.class
  p c.degree
  p c.knots
  p c.mults
  p c.poles
  p c.weights
  p curve(c, 0, 1).terms
end
