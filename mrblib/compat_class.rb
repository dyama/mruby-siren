##
#
# Compatibility class
#
#

{
  BRepIO: {
    save: "save_brep",
    load: "load_brep",
    dump: "dump",
  },
  IGES: {
    save: "save_iges",
    load: "load_iges"
  },
  STL: {
    save: "save_stl",
    load: "load_stl"
  },
  STEP: {
    save: "save_step",
    load: "load_step"
  },
  Prim: {
    box:        "box",
    box2p:      "box2p",
    boxax:      "boxax",
    sphere:     "sphere",
    cylinder:   "cylinder",
    cone:       "cone",
    torus:      "torus",
    halfspace:  "halfspace",
    prism:      "prism",
    revol:      "revol",
    revolution: "revolution",
    wedge:      "wedge",
  },
}.each do |mod, ms|
  newmod = self.class.const_set mod, Module.new
  ms.each do |from, dest|
    newmod.define_singleton_method(from) do |*args|
      Siren.warn "#{mod}.#{from} is an abolished method. Use Siren.#{dest} instead."
      Siren.send(dest, *args)
    end
  end
end

