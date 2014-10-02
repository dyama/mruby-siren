#!ruby

degree = 2
# knots = [0, 0, 0, 1, 2, 2, 2]
# use commpressed knot array
knots = [0.0, 1.0, 2.0]
mults = [3, 1, 3]
poles = [Vec.new(10, 0, 7), Vec.new(7, 0, 7), Vec.new(3, 0, 8), Vec.new(0, 0, 7)]
weights = [1.0, 1.0, 1.0, 1.0]

c = Build.nurbscurve degree, knots, mults, poles#, weights

p c

