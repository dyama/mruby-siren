##
#
# Siren module
#

module Siren
  [
    # STEP package
    [STEP, "save", "save_step"],
    [STEP, "load", "load_step"],
    # STL package
    [STL, "save", "save_stl"],
    [STL, "load", "load_stl"],
    # IGES package
    [IGES, "save", "save_iges"],
    [IGES, "load", "load_iges"],
  ].each do |ary|
    package, method, export = ary
    define_method(export) do |*args|
      package.send(method, *args)
    end
    define_singleton_method(export) do |*args|
      package.send(method, *args)
    end
  end
  include BRepIO
  include Build
  include Offset
  include Prim
end

