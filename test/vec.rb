#!siren
# coding: utf-8

# Test script for Vec class.

p Vec::origin
p Vec::zero
p Vec::xdir
p Vec::ydir
p Vec::zdir

p Vec::new(1, 1, 1) + Vec::new(0, 0, 1)
p Vec::new(1, 1, 1) - Vec::new(0, 0, 1)
p Vec::new(1, 1, 1) * 2
p Vec::new(1, 1, 1) / 2

p -Vec::xdir * 10
p Vec::new(10, 10, 0) == Vec::new(10, 10, 0) # => true
p Vec::new(10, 10, 1) == Vec::new(10, 10, 0) # => false
p Vec::new(10, 10, 0) != Vec::new(10, 10, 0) # => false
p Vec::new(10, 10, 1) != Vec::new(10, 10, 0) # => true

