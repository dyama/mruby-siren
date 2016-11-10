#include "topalgo.h"

bool siren_topalgo_install(mrb_state* mrb, struct RClass* mod_siren)
{
  // Class method
  mrb_define_class_method(mrb, mod_siren, "copy",       siren_topalgo_copy,       MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, mod_siren, "line",       siren_topalgo_line,       MRB_ARGS_OPT(2));
  mrb_define_class_method(mrb, mod_siren, "infline",    siren_topalgo_infline,    MRB_ARGS_OPT(2));
  mrb_define_class_method(mrb, mod_siren, "polyline",   siren_topalgo_polyline,   MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, mod_siren, "interpolate",siren_topalgo_interpolate,MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, mod_siren, "arc",        siren_topalgo_arc,        MRB_ARGS_REQ(6));
  mrb_define_class_method(mrb, mod_siren, "arc3p",      siren_topalgo_arc3p,      MRB_ARGS_REQ(3));
  mrb_define_class_method(mrb, mod_siren, "circle",     siren_topalgo_circle,     MRB_ARGS_REQ(3));
  mrb_define_class_method(mrb, mod_siren, "circle3p",   siren_topalgo_circle3p,   MRB_ARGS_REQ(3));
  // For mix-in
  mrb_define_method      (mrb, mod_siren, "copy",       siren_topalgo_copy,       MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_method      (mrb, mod_siren, "line",       siren_topalgo_line,       MRB_ARGS_REQ(2));
  mrb_define_method      (mrb, mod_siren, "infline",    siren_topalgo_infline,    MRB_ARGS_REQ(2));
  mrb_define_method      (mrb, mod_siren, "polyline",   siren_topalgo_polyline,   MRB_ARGS_REQ(1));
  mrb_define_method      (mrb, mod_siren, "interpolate",siren_topalgo_interpolate,MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_method      (mrb, mod_siren, "arc",        siren_topalgo_arc,        MRB_ARGS_REQ(6));
  mrb_define_method      (mrb, mod_siren, "arc3p",      siren_topalgo_arc3p,      MRB_ARGS_REQ(3));
  mrb_define_method      (mrb, mod_siren, "circle",     siren_topalgo_circle,     MRB_ARGS_REQ(3));
  mrb_define_method      (mrb, mod_siren, "circle3p",   siren_topalgo_circle3p,   MRB_ARGS_REQ(3));

  struct RClass* cls_shape = siren_shape_rclass(mrb);
  mrb_define_method(mrb, cls_shape, "cog",    siren_topalgo_cog,    MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "area",   siren_topalgo_area,   MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "volume", siren_topalgo_volume, MRB_ARGS_NONE());
  return true;
}

mrb_value siren_topalgo_copy(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  mrb_bool copy_geom = (mrb_bool)Standard_True;
  int argc = mrb_get_args(mrb, "o|b", &target, &copy_geom);
  TopoDS_Shape* src = siren_shape_get(mrb, target);
  TopoDS_Shape res = BRepBuilderAPI_Copy(*src, (Standard_Boolean)copy_geom);
  return siren_shape_new(mrb, res);
}

mrb_value siren_topalgo_line(mrb_state* mrb, mrb_value self)
{
  mrb_value sp, tp;
  int argc = mrb_get_args(mrb, "|AA", &sp, &tp);
  gp_Pnt S(0., 0., 0.);
  gp_Pnt T(1., 1., 1.);
  if (argc > 0) {
    S = siren_ary_to_pnt(mrb, sp);
  }
  if (argc > 1) {
    T = siren_ary_to_pnt(mrb, tp);
  }
  Standard_Real linear_tolerance = 1.0e-7;
  if (S.IsEqual(T, linear_tolerance)) {
    mrb_raise(mrb, E_ARGUMENT_ERROR,
        "Specified terminal point same as the start point.");
  }
  TopoDS_Shape shape = BRepBuilderAPI_MakeEdge(S, T);
  return siren_shape_new(mrb, shape);
}

mrb_value siren_topalgo_infline(mrb_state* mrb, mrb_value self)
{
  mrb_value orig, dir;
  int argc = mrb_get_args(mrb, "|AA", &orig, &dir);
  gp_Pnt p(0., 0., 0.);
  gp_Dir d(1., 0., 0.);
  if (argc > 0) {
    p = siren_ary_to_pnt(mrb, orig);
  }
  if (argc > 1) {
    d = siren_ary_to_dir(mrb, dir);
  }
  TopoDS_Shape shape = BRepBuilderAPI_MakeEdge(gp_Lin(p, d));
  return siren_shape_new(mrb, shape);
}

mrb_value siren_topalgo_polyline(mrb_state* mrb, mrb_value self)
{
  mrb_value ary;
  int argc = mrb_get_args(mrb, "A", &ary);
  BRepBuilderAPI_MakePolygon poly;
  for (int i = 0; i < mrb_ary_len(mrb, ary); i++) {
    poly.Add(siren_ary_to_pnt(mrb, mrb_ary_ref(mrb, ary, i)));
  }
  TopoDS_Shape shape = poly.Wire();
  return siren_shape_new(mrb, shape);
}

mrb_value siren_topalgo_interpolate(mrb_state* mrb, mrb_value self)
{
  mrb_value pts, vecs;
  int argc = mrb_get_args(mrb, "A|A", &pts, &vecs);

  int psize = mrb_ary_len(mrb, pts);
  opencascade::handle<TColgp_HArray1OfPnt> pary = new TColgp_HArray1OfPnt(1, psize);
  for (int i=0; i<psize; i++) {
    pary->SetValue(i+1, siren_ary_to_pnt(mrb, mrb_ary_ref(mrb, pts, i)));
  }

  try {
    Standard_Real tolerance = 1.0e-7;
    Standard_Boolean periodic_flag = Standard_False;

    // Raise exception when got pary has same points.
    GeomAPI_Interpolate intp(pary, periodic_flag, tolerance);

    if (argc == 2) {
      TColgp_Array1OfVec vec(1, psize);
      opencascade::handle<TColStd_HArray1OfBoolean> use = new TColStd_HArray1OfBoolean(1, psize);

      for (int i=0; i<psize; i++) {
        mrb_value avec = mrb_ary_ref(mrb, vecs, i);
        if (mrb_nil_p(avec)) {
          use->SetValue(i+1, Standard_False);
        }
        else {
          vec.SetValue(i+1, siren_ary_to_vec(mrb, avec));
          use->SetValue(i+1, Standard_True);
        }
      }
      intp.Load(vec, use, Standard_True);
    }

    intp.Perform();
    if (!intp.IsDone()) {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a curve.");
    }

    opencascade::handle<Geom_BSplineCurve> geSpl = intp.Curve();
    if (geSpl.IsNull()) {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a curve.");
    }

    TopoDS_Shape shape = BRepBuilderAPI_MakeEdge(geSpl);
    return siren_shape_new(mrb, shape);
  }
  catch (...) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a curve. Incorrect points specified.");
  }
  return mrb_nil_value();
}

mrb_value siren_topalgo_arc(mrb_state* mrb, mrb_value self)
{
  mrb_value orig, dir, vx;
  mrb_float r, start_ang, term_ang;
  int argc = mrb_get_args(mrb, "AAAfff", &orig, &dir, &vx, &r, &start_ang, &term_ang);
  gp_Circ circle = gp_Circ(gp_Ax2(siren_ary_to_pnt(mrb, orig), siren_ary_to_dir(mrb, dir), siren_ary_to_dir(mrb, vx)), r);
  opencascade::handle<Geom_TrimmedCurve> gc = GC_MakeArcOfCircle(circle, start_ang, term_ang, Standard_True);
  if (gc.IsNull()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a curve.");
    return mrb_nil_value();
  }
  else {
    TopoDS_Edge E = BRepBuilderAPI_MakeEdge(gc);
    return siren_shape_new(mrb, E);
  }
}

mrb_value siren_topalgo_arc3p(mrb_state* mrb, mrb_value self)
{
  mrb_value p1, p2, p3;
  int argc = mrb_get_args(mrb, "AAA", &p1, &p2, &p3);
  opencascade::handle<Geom_TrimmedCurve> gc = GC_MakeArcOfCircle(
      siren_ary_to_pnt(mrb, p1),
      siren_ary_to_pnt(mrb, p2),
      siren_ary_to_pnt(mrb, p3));
  if (gc.IsNull()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a curve.");
    return mrb_nil_value();
  }
  else {
    TopoDS_Edge E = BRepBuilderAPI_MakeEdge(gc);
    return siren_shape_new(mrb, E);
  }
}

mrb_value siren_topalgo_circle(mrb_state* mrb, mrb_value self)
{
  mrb_value orig, dir;
  mrb_float r;
  int argc = mrb_get_args(mrb, "AAf", &orig, &dir, &r);
  opencascade::handle<Geom_Circle> gc = GC_MakeCircle(
      siren_ary_to_pnt(mrb, orig),
      siren_ary_to_dir(mrb, dir),
      r);
  if (gc.IsNull()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a curve.");
    return mrb_nil_value();
  }
  else {
    TopoDS_Edge E = BRepBuilderAPI_MakeEdge(gc);
    return siren_shape_new(mrb, E);
  }
}

mrb_value siren_topalgo_circle3p(mrb_state* mrb, mrb_value self)
{
  mrb_value p1, p2, p3;
  int argc = mrb_get_args(mrb, "AAA", &p1, &p2, &p3);
  opencascade::handle<Geom_Circle> gc = GC_MakeCircle(
      siren_ary_to_pnt(mrb, p1),
      siren_ary_to_pnt(mrb, p2),
      siren_ary_to_pnt(mrb, p3));
  if (gc.IsNull()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a curve.");
    return mrb_nil_value();
  }
  else {
    TopoDS_Edge E = BRepBuilderAPI_MakeEdge(gc);
    return siren_shape_new(mrb, E);
  }
}

mrb_value siren_topalgo_volume(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  GProp_GProps gprops;
  BRepGProp::VolumeProperties(*shape, gprops);
  Standard_Real vol = gprops.Mass();
  return mrb_float_value(mrb, (mrb_float)vol);
}

mrb_value siren_topalgo_cog(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  GProp_GProps gprops;
  BRepGProp::VolumeProperties(*shape, gprops);
  gp_Pnt cog = gprops.CentreOfMass();
  return siren_pnt_to_ary(mrb, cog);
}

mrb_value siren_topalgo_area(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  GProp_GProps gprops;
  BRepGProp::SurfaceProperties(*shape, gprops);
  Standard_Real area = gprops.Mass();
  return mrb_float_value(mrb, area);
}

