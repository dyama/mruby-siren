##
#
# Siren module
#

module Siren
  {
    # Prim package
    box:             Prim,
    box2p:           Prim,
    boxax:           Prim,
    sphere:          Prim,
    cylinder:        Prim,
    cone:            Prim,
    torus:           Prim,
    halfspace:       Prim,
    prism:           Prim,
    revol:           Prim,
    revolution:      Prim,
    wedge:           Prim,
    # Build package
    copy:            Build,
    vertex:          Build,
    line:            Build,
    infline:         Build,
    polyline:        Build,
    curve:           Build,
    wire:            Build,
    arc:             Build,
    arc3p:           Build,
    circle:          Build,
    circle3p:        Build,
    plane:           Build,
    face:            Build,
    infplane:        Build,
    polygon:         Build,
    nurbscurve:      Build,
    beziersurf:      Build,
    nurbssurf:       Build,
    sewing:          Build,
    solid:           Build,
    compound:        Build,
    # BRepIO package
    save:            BRepIO,
    load:            BRepIO,
    dump:            BRepIO,
    # Offset package
    sweep_vec:       Offset,
    sweep_path:      Offset,
    loft:            Offset,
    offset_geomsurf: Offset,
    offset:          Offset,
    offset_shape:    Offset,
    pipe:            Offset,
  }.each do |method, package|
    define_method(method) do |*args|
      package.send(method, *args)
    end
    define_singleton_method(method) do |*args|
      package.send(method, *args)
    end
  end
end

