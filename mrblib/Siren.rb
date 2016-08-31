##
#
# Siren module
#

module Siren
  [
    # BRepIO package
    [BRepIO, "save", "save_brep"],
    [BRepIO, "load", "load_brep"],
    [BRepIO, "dump", "dump"],
    # STEP package
    [STEP, "save", "save_step"],
    [STEP, "load", "load_step"],
  ].each do |ary|
    package, method, export = ary
    define_method(export) do |*args|
      package.send(method, *args)
    end
    define_singleton_method(export) do |*args|
      package.send(method, *args)
    end
  end
  extend Build
  extend Heal
  extend Offset
  extend Prim
  include Build
  include Heal
  include Offset
  include Prim

  def self.warn(*msg)
    return if $VERBOSE.nil? && msg.empty?
    $stderr.puts("siren: warning: " + msg.join)
  end

end

