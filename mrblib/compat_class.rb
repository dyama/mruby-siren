##
#
# Compatibility class
#
#

{
  STL: {
    save: "save_stl",
    load: "load_stl"
  },
  IGES: {
    save: "save_iges",
    load: "load_iges"
  }
}.each do |mod, ms|
  newmod = self.class.const_set mod, Module.new
  ms.each do |from, dest|
    newmod.define_singleton_method(from) do |*args|
      Siren.warn "#{mod}.#{from} is an abolished method. Use Siren.#{dest} instead."
      Siren.send(dest, *args)
    end
  end
end

