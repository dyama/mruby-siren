##
#
# Siren module
#

module Siren

  {
    box: Prim,
    copy: Build,
    vertex: Build,
    line: Build,
    infline: Build,
  }.each do |method, package|
    define_method(method) do |*args|
      package.send(method, *args)
    end
    define_singleton_method(method) do |*args|
      package.send(method, *args)
    end
  end

end
