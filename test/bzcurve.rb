#!/usr/bin/env siren
# coding: utf-8

include Siren

poles = [[0, 0, 0], [1, 2, 0], [3, 2, 0], [4, 0, 0]]
weights = [1.0, 1.2, 1.0, 1.0]

if true
  e = bzcurve poles, weights, 0.1, 0.9
  p e
  p e.curve.class
  p e.length
  # p e.curve.degree
  # p e.curve.poles
  # p e.curve.weights
else
  c = BzCurve.new poles, weights
  p c
  p c.class
  # p c.degree
  # p c.poles
  # p c.weights
  p Edge.new(c, 0, 1).terms
end

