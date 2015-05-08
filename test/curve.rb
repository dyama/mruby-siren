#!/usr/bin/env siren
# coding: utf-8

degree = 2
# knots = [0, 0, 0, 1, 2, 2, 2]
# use commpressed knot array
knots = [0.0, 1.0, 2.0]
mults = [3, 1, 3]
poles = [[10, 0, 7], [7, 0, 7], [3, 0, 8], [0, 0, 7]]
weights = [1.0, 1.0, 1.0, 1.0]

c = Build.nurbscurve degree, knots, mults, poles#, weights
p c
p c.nurbs_def

