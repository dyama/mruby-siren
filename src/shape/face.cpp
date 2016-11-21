#include "shape/face.h"

mrb_value siren_face_new(mrb_state* mrb, const TopoDS_Shape* src)
{
  mrb_value obj;
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Face")));
  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = *src; // Copy to inner native member
  DATA_PTR(obj)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(obj) = &siren_face_type;
  return obj;
}

TopoDS_Face siren_face_get(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, self, &siren_face_type));
  TopoDS_Face face = TopoDS::Face(*shape);
  if (face.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Face."); }
  return face;
}

bool siren_face_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* cls_face = mrb_define_class_under(mrb, mod_siren, "Face", cls_shape);
  MRB_SET_INSTANCE_TT(cls_face, MRB_TT_DATA);
  mrb_define_method(mrb, cls_face, "initialize", siren_shape_init,     MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_face, "normal",     siren_face_normal,    MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_face, "to_bezier",  siren_face_to_bezier, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_face, "split",      siren_face_split,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_face, "triangle",   siren_face_triangle,  MRB_ARGS_REQ(2));

  auto obj_face = mrb_obj_ptr(siren_face_obj(mrb));
  mrb_define_singleton_method(mrb, obj_face, "plane",    siren_face_plane,    MRB_ARGS_REQ(7));
  mrb_define_singleton_method(mrb, obj_face, "face",     siren_face_face,     MRB_ARGS_REQ(2));
  mrb_define_singleton_method(mrb, obj_face, "infplane", siren_face_infplane, MRB_ARGS_REQ(2));
  mrb_define_singleton_method(mrb, obj_face, "polygon",  siren_face_polygon,  MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_singleton_method(mrb, obj_face, "bzsurf",   siren_face_bzsurf,   MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_singleton_method(mrb, obj_face, "bssurf",   siren_face_bssurf,   MRB_ARGS_REQ(5) | MRB_ARGS_OPT(1));
  return true;
}

struct RClass* siren_face_rclass(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Face")));
}

mrb_value siren_face_normal(mrb_state* mrb, mrb_value self)
{
  TopoDS_Face f = siren_face_get(mrb, self);
  Standard_Real umin, umax, vmin, vmax;
  BRepTools::UVBounds(f, umin, umax, vmin, vmax);
  handle<Geom_Surface> gsurf = BRep_Tool::Surface(f);
  GeomLProp_SLProps props(gsurf, umin, vmin, 1, 0.01);
  gp_Dir n = props.Normal();
  return siren_vec_new(mrb, n.X(), n.Y(), n.Z());
}

mrb_value siren_face_to_bezier(mrb_state* mrb, mrb_value self)
{
  TopoDS_Face face = siren_face_get(mrb, self);
  handle<Geom_Surface> gsurf  = BRep_Tool::Surface(face);
  handle<Geom_BSplineSurface> gbssurf = handle<Geom_BSplineSurface>::DownCast(gsurf);
  if (gbssurf.IsNull()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Specified shape is not B-Spline surface.");
  }

  TopoDS_Compound comp;
  BRep_Builder B;
  B.MakeCompound(comp);

  GeomConvert_BSplineSurfaceToBezierSurface converter(gbssurf);

  TColGeom_Array2OfBezierSurface ary(1, converter.NbUPatches(), 1, converter.NbVPatches());
  converter.Patches(ary);

  for (int r = ary.LowerRow(); r <= ary.UpperRow(); r++) {
    for (int c = ary.LowerCol(); c <= ary.UpperCol(); c++) {
      handle<Geom_BezierSurface> gbzsurf = ary.Value(r, c);
      TopoDS_Face patch = BRepBuilderAPI_MakeFace(gbzsurf, 1.0e-1);
      B.Add(comp, patch);
    }
  }

  return siren_shape_new(mrb, comp);
}

mrb_value siren_face_split(mrb_state* mrb, mrb_value self)
{
  mrb_value obj;
  int argc = mrb_get_args(mrb, "o", &obj);

  TopoDS_Face face = siren_face_get(mrb, self);
  BRepFeat_SplitShape splitter(face);

  TopoDS_Shape shape = *siren_shape_get(mrb, obj);
  switch (shape.ShapeType()) {
  case TopAbs_WIRE:
    splitter.Add(TopoDS::Wire(shape), face);
    break;
  case TopAbs_EDGE:
    splitter.Add(TopoDS::Edge(shape), face);
    break;
  case TopAbs_COMPOUND:
    splitter.Add(TopoDS::Compound(shape), face);
    break;
  default:
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Incorrect argument specified.");
  }
  try {
    splitter.Build();
  }
  catch (...) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Failed to split the face.");
  }
  if (!splitter.IsDone()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Failed to split the face.");
  }
  return siren_shape_new(mrb, splitter.Shape());
}

mrb_value siren_face_triangle(mrb_state* mrb, mrb_value self)
{
  mrb_float deflection, angle;
  int argc = mrb_get_args(mrb, "ff", &deflection, &angle);

  mrb_value result = mrb_ary_new(mrb);

  TopoDS_Face face = siren_face_get(mrb, self);
  BRepTools::Update(face);

  BRepMesh_IncrementalMesh imesh(face, deflection, Standard_False, angle);
  imesh.Perform();
  if (!imesh.IsDone()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to incremantal mesh.");
  }

  TopoDS_Face face2 = TopoDS::Face(imesh.Shape());

  TopLoc_Location loc;
  // Do triangulation
  handle<Poly_Triangulation> poly = BRep_Tool::Triangulation(face2, loc);
  if (poly.IsNull()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to triangulation.");
  }

  const Poly_Array1OfTriangle& tris = poly->Triangles();

  for (Standard_Integer i = tris.Lower(); i <= tris.Upper(); i++) {

    const Poly_Triangle& tri = tris.Value(i);

    // Node indexes
    Standard_Integer n1, n2, n3;
    if (face2.Orientation() != TopAbs_REVERSED) {
      tri.Get(n1, n2, n3);
    }
    else {
      tri.Get(n3, n2, n1);
    }

    gp_Pnt p1 = poly->Nodes().Value(n1);
    gp_Pnt p2 = poly->Nodes().Value(n2);
    gp_Pnt p3 = poly->Nodes().Value(n3);

    p1.Transform(loc);
    p2.Transform(loc);
    p3.Transform(loc);

    gp_Vec u = gp_Vec(p2.XYZ() - p1.XYZ());
    gp_Vec v = gp_Vec(p3.XYZ() - p1.XYZ());

    gp_Vec norm(
        u.Y() * v.Z() - u.Z() * v.Y(),
        u.Z() * v.X() - u.X() * v.Z(),
        u.X() * v.Y() - u.Y() * v.X());
    if (norm.Magnitude() <= 0) {
      continue;
    }
    norm.Normalize();

    mrb_value trimesh = mrb_ary_new(mrb);
    mrb_ary_push(mrb, trimesh, siren_pnt_to_ary(mrb, p1));
    mrb_ary_push(mrb, trimesh, siren_pnt_to_ary(mrb, p2));
    mrb_ary_push(mrb, trimesh, siren_pnt_to_ary(mrb, p3));
    mrb_ary_push(mrb, trimesh, siren_vec_to_ary(mrb, u));
    mrb_ary_push(mrb, trimesh, siren_vec_to_ary(mrb, v));
    mrb_ary_push(mrb, trimesh, siren_vec_to_ary(mrb, norm));

    mrb_ary_push(mrb, result, trimesh);
  }

  return result;
}

mrb_value siren_face_obj(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Face"));
}

mrb_value siren_face_plane(mrb_state* mrb, mrb_value self)
{
  mrb_value pos, norm, vx;
  mrb_float umin, umax, vmin, vmax;
  int argc = mrb_get_args(mrb, "AAAffff", &pos, &norm, &vx, &umin, &umax, &vmin, &vmax);
  try {
    gp_Pln _pln(siren_ary_to_ax2(mrb, pos, norm, vx));
    BRepBuilderAPI_MakeFace face(_pln, umin, umax, vmin, vmax);
    return siren_shape_new(mrb, face.Shape());
  }
  catch (...) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a plane. "
        "vx has same value with the normal vector.");
    return mrb_nil_value();
  }
}

mrb_value siren_face_face(mrb_state* mrb, mrb_value self)
{
  mrb_value wire;
  mrb_bool force_plane;
  int argc = mrb_get_args(mrb, "ob", &wire, &force_plane);
  TopoDS_Shape* s = siren_shape_get(mrb, wire);
  TopoDS_Wire w = TopoDS::Wire(*s);
  if (w.IsNull()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Specified shape type is not wire.");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(w, (Standard_Boolean)force_plane);
  return siren_shape_new(mrb, face);
}

mrb_value siren_face_infplane(mrb_state* mrb, mrb_value self)
{
  mrb_value orig, dir;
  int argc = mrb_get_args(mrb, "AA", &orig, &dir);
  gp_Pln pln(siren_ary_to_pnt(mrb, orig), siren_ary_to_dir(mrb, dir));
  TopoDS_Face face = BRepBuilderAPI_MakeFace(pln);
  return siren_shape_new(mrb, face);
}

mrb_value siren_face_polygon(mrb_state* mrb, mrb_value self)
{
  mrb_value pts;
  mrb_bool force_plane = (mrb_bool)Standard_True;
  int argc = mrb_get_args(mrb, "A|b", &pts, &force_plane);

  BRepBuilderAPI_MakePolygon mp;

  for (int i=0; i<mrb_ary_len(mrb, pts); i++) {
    mp.Add(siren_ary_to_pnt(mrb, mrb_ary_ref(mrb, pts, i)));
  }

  mp.Close();
  BRepBuilderAPI_MakeFace mf(mp.Wire(), force_plane);
  mf.Build();

  if (!mf.IsDone()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a polygon.");
  }

  return siren_shape_new(mrb, mf.Shape());
}

mrb_value siren_face_bzsurf(mrb_state* mrb, mrb_value self)
{
  mrb_value ptary, wtary;
  int argc = mrb_get_args(mrb, "A|A", &ptary, &wtary);

  int rlen = mrb_ary_len(mrb, ptary);
  int clen = mrb_ary_len(mrb, mrb_ary_ref(mrb, ptary, 0));

  TColgp_Array2OfPnt poles(0, rlen-1, 0, clen-1);

  for (int r=0; r<rlen; r++) {
    mrb_value ar = mrb_ary_ref(mrb, ptary, r);
    for (int c=0; c<clen; c++) {
      poles.SetValue(r, c, siren_ary_to_pnt(mrb, mrb_ary_ref(mrb, ar, c)));
    }
  }

  opencascade::handle<Geom_BezierSurface> s = nullptr;

  if (argc == 2) {
    TColStd_Array2OfReal weights(0, rlen-1, 0, clen-1);
    for (int r=0; r<rlen; r++) {
      mrb_value ar = mrb_ary_ref(mrb, wtary, r);
      for (int c=0; c<clen; c++) {
        mrb_value val = mrb_ary_ref(mrb, ar, c);
        weights.SetValue(r, c, mrb_float(val));
      }
    }
    s = new Geom_BezierSurface(poles, weights);
  }
  else {
    s = new Geom_BezierSurface(poles);
  }

  return siren_shape_new(mrb, BRepBuilderAPI_MakeFace(s, 1.0e-7));
}

mrb_value siren_face_bssurf(mrb_state* mrb, mrb_value self)
{
  mrb_int _udeg, _vdeg;
  mrb_value _ar_ukm, _ar_vkm;
  mrb_value _pol;
  mrb_value _wire;
  int argc = mrb_get_args(mrb, "iAiAA|o", &_udeg, &_ar_ukm, &_vdeg, &_ar_vkm, &_pol, &_wire);

  bool has_contour = argc == 6;

  Standard_Integer udeg = _udeg;
  Standard_Integer nbuknots = mrb_ary_len(mrb, _ar_ukm);
  Standard_Integer nbuknots_pure = 0;
  TColStd_Array1OfReal uknots(1, nbuknots);
  TColStd_Array1OfInteger umults(1, nbuknots);
  for (int i=1; i<=nbuknots; i++) {
    mrb_value item = mrb_ary_ref(mrb, _ar_ukm, i - 1);
    mrb_value knot = mrb_ary_ref(mrb, item, 0);
    mrb_value mult = mrb_ary_ref(mrb, item, 1);
    uknots(i) = mrb_float(knot);
    umults(i) = mrb_fixnum(mult);
    nbuknots_pure += umults(i);
  }
  Standard_Integer nbupoles = nbuknots_pure - udeg - 1;

  Standard_Integer vdeg = _vdeg;
  Standard_Integer nbvknots = mrb_ary_len(mrb, _ar_vkm);
  Standard_Integer nbvknots_pure = 0;
  TColStd_Array1OfReal vknots(1, nbvknots);
  TColStd_Array1OfInteger vmults(1, nbvknots);
  for (int i=1; i<=nbvknots; i++) {
    mrb_value item = mrb_ary_ref(mrb, _ar_vkm, i - 1);
    mrb_value knot = mrb_ary_ref(mrb, item, 0);
    mrb_value mult = mrb_ary_ref(mrb, item, 1);
    vknots(i) = mrb_float(knot);
    vmults(i) = mrb_fixnum(mult);
    nbvknots_pure += vmults(i);
  }
  Standard_Integer nbvpoles = nbvknots_pure - vdeg - 1;

  TColgp_Array2OfPnt   poles  (1, nbupoles, 1, nbvpoles);
  TColStd_Array2OfReal weights(1, nbupoles, 1, nbvpoles);

  for (int v=1; v <= nbvpoles; v++) {
    mrb_value vitem = mrb_ary_ref(mrb, _pol, v - 1);
    for (int u=1; u <= nbupoles; u++) {
      mrb_value uitem = mrb_ary_ref(mrb, vitem, u - 1);
      poles.SetValue(u, v, siren_ary_to_pnt(mrb, mrb_ary_ref(mrb, uitem, 0)));
      weights.SetValue(u, v, mrb_float(mrb_ary_ref(mrb, uitem, 1)));
    }
  }

  opencascade::handle<Geom_BSplineSurface> hg_bssurf = new Geom_BSplineSurface(poles, weights, uknots, vknots, umults, vmults, udeg, vdeg);
  TopoDS_Shape shape;
  if (has_contour) {
    TopoDS_Shape* s = siren_shape_get(mrb, _wire);
    TopoDS_Wire w = TopoDS::Wire(*s);
    shape = BRepBuilderAPI_MakeFace(hg_bssurf, w, Standard_True);
    // Fix a face
    opencascade::handle<ShapeFix_Shape> sfs = new ShapeFix_Shape();
    sfs->Init(shape);
    sfs->FixFaceTool()->FixAddNaturalBoundMode() = 1;
    sfs->FixFaceTool()->FixIntersectingWiresMode() = 1;
    sfs->FixFaceTool()->FixLoopWiresMode() = 1;
    sfs->FixFaceTool()->FixOrientationMode() = 1;
    sfs->FixFaceTool()->FixPeriodicDegeneratedMode() = 1;
    sfs->FixFaceTool()->FixSmallAreaWireMode() = 1;
    sfs->FixFaceTool()->FixSplitFaceMode() = 1;
    sfs->FixFaceTool()->FixWireMode() = 1;
    sfs->SetPrecision(1.0);
    sfs->SetMinTolerance(1.0e-1);
    sfs->SetMaxTolerance(1.0);
    sfs->Perform();
    shape = sfs->Shape();
    // End of fix
  }
  else {
    Standard_Real toldegen = 1.0e-1;
    shape = BRepBuilderAPI_MakeFace(hg_bssurf, toldegen);
  }

  return siren_shape_new(mrb, shape);
}

