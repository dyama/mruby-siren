siren Reference Manual
======================

Classes
-------
* BndBox - _Bnd_Box_
  * min -> Vec
  * max -> Vec
* Shape - _TopoDS_Shape_
  * bndbox -> BndBox
  * equal?(shape) -> bool
  * explore(ShapeType){ |shape, depth| ... } -> self
  * hashcode(upper) -> Integer
  * location -> (Vec)
  * null? -> bool
  * mirror(op, norm) -> Shape
  * mirror!(op, norm) -> nil
  * move(Trans) -> Shape
  * move!(Trans) -> nil
  * to_s -> String
  * translate(Vec) -> Shape
  * translate!(Vec) -> nil
  * rotate(op, norm, angle) -> Shape
  * rotate!(op, norm, angle) -> nil
  * partner?(shape) -> bool
  * same?(shape) -> bool
  * scale(op, factor) -> Shape
  * scale!(op, factor) -> nil
  * shapetype -> Integer(to be ShapeType)
  * section(shape1, shape2) -> Shape
* Singleton methods of Shape
  * ShapeType::VERTEX
  * ShapeType::EDGE - _TopoDS_Edge_
    * sp -> Vec
    * tp -> Vec
    * to_pts(deflection = 1.0e-1) -> Ary[Vec]
    * param(Vec) -> Float
    * to_xyz(param) -> Vec
    * curvature(param) -> Vec
    * tangent(param) -> Vec
  * ShapeType::WIRE
  * ShapeType::FACE
    * to_bezier -> Shape
  * ShapeType::SHELL
  * ShapeType::SOLID
  * ShapeType::COMPOUND
* Trans - _gp_Trsf_
  * new -> Trans
  * mirror!(op, norm) -> nil
  * multiply!(Trans) -> nil
  * multiply(Trans) -> Trans
  * rotation!(op, norm, angle) -> nil
  * scale!(op, factor) -> nil
  * scalef -> Float
  * scalef! -> nil
  * transformation1!(op, zv, xv) -> nil
  * transformation2!(op1, zv1, xv1, op2, zv2, xv2) -> nil
  * translation!(vector) -> nil
* Vec - _gp_Vec_
  * new(x, y, z) -> Vec
  * to_a -> Array
  * to_s -> String
  * to_xyz -> Array[x, y, z]
  * x -> Float
  * y -> Float
  * z -> Float
  * x=
  * y=
  * z=
  * equal?(other, liner_tolerance, angular_tolerance) -> bool
  * normal?(other, angular_tolerance) -> bool
  * opposite?(other, angular_tolerance) -> bool
  * parallel?(other, angular_tolerance) -> bool
  * normalize -> Vec
  * normalize! -> self
  * reverse -> Vec
  * reverse! -> self
  * angle(other) -> Float
  * magnitude, size, length -> Float
  * -@ -> Vec
  * + -> Vec
  * - -> Vec
  * * -> Vec
  * / -> Vec
* Skin - _AIS_Shape_
  * new(shape) -> Skin
  * color -> ColorName
  * color=(ColorName) -> nil
  * material -> MaterianName
  * material=(MaterialName) -> nil
  * transparency -> Float
  * transparency=(value)
* World - _AIS_InteractiveContext_, _V3d_Viewer_
  * new(display) -> World
  * add(skin) -> nil
  * erase(skin) -> nil
* Camera - _V3d_View_
  * new(world, Pointer of X Window) -> Camera
  * fit -> nil

Modules
-------

* Bool - _TKBool_
  * common(shape1, shape2) -> Shape
  * cut(shape1, shape2) -> Shape
  * fuse(shape1, shape2) -> Shape
  * projwire(wire, face, vec) -> Shape
* BRepIO - _TKBRep_ - _BRepTools_
  * load(path) -> Shape
  * save(shape, path) -> nil
* Build - _TKBRep_ - _BRep_ - _BRepBuilderAPI_
  * compound(Array[shape]) -> Shape
  * copy(shape) -> Shape
  * curve(Array[point], Array[Vec]) -> Shape
  * line(sp, tp) -> Shape
  * plane(pos, norm, vdir, umin, umax, vmin, vmax) -> Shape
  * polygon(Array[point]) -> Shape
  * polyline(Array[point]) -> Shape
  * nrubscurve(degree, knots, mults, poles, weights) -> Shape
  * beziersurf(poles[][], weights[][]) -> Shape
  * sewing(Array[face], tolerance = nil) -> Shape
  * solid(shell) -> Shape
  * vertex(x, y, z) -> Shape
* Feat - _TKFeat_
  * splitFxW(face, wire) -> Shape
* GProp - _TKG2d_ - _GProp_
  * area(shape) -> Float
  * cog(shape) -> Vec
  * volume(shape) -> Float
* Heal - _TKShHealing_
  * outerwire(shape) -> Shape
* IGES - _TKIGES_
  * load(path, one_shape = false) -> Shape | Array[Shape]
  * save(Array[shape], path) -> nil
* Offset - _TKOffset_
  * loft(Array[wire], smooth = true, is_solod = false, is_ruled = true) -> Shape
  * offset(shape, distance, tolerance = 1.0) -> Shape
  * sweep_path(shape, edge/wire) -> Shape
  * sweep_vec(shape, vec) -> Shape
* Prim - _TKPrim_
  * box(size, pos = Vec[0, 0, 0]) -> Shape
  * cone(pos, norm, r1, r2, height, angle) -> Shape
  * cylinder(pos, norm, r, height, angle) -> Shape
  * sphere(r, pos = Vec[0, 0, 0]) -> Shape
  * torus(pos, norm, r1, r2, angle) -> Shape
  * _halfspace_
  * _oneaxis_
  * _prism_
  * _revol_
  * _revolution_
  * _sweep_
  * _wedge_

Embedded ruby modules
---------------------

These module are used as enum-type by siren script and interface of any methods. In many cases, these can be replaced by an integer value.

* ShapeType
* OrientType
* MaterialName
* ColorName
