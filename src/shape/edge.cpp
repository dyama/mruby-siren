#include "shape/edge.h"

void siren_edge_install(mrb_state* mrb, RObject* o)
{
  mrb_define_singleton_method(mrb, o, "sp",        siren_edge_sp,        MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "tp",        siren_edge_tp,        MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "to_pts",    siren_edge_to_pts,    MRB_ARGS_OPT(1));
  mrb_define_singleton_method(mrb, o, "param",     siren_edge_param,     MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_singleton_method(mrb, o, "to_xyz",    siren_edge_to_xyz,    MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, o, "curvature", siren_edge_curvature, MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, o, "tangent",   siren_edge_tangent,   MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, o, "nurbs_def", siren_edge_nurbs_def, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "extrema",   siren_edge_extrema,   MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, o, "split",     siren_edge_split,     MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, o, "trim",      siren_edge_trim,      MRB_ARGS_REQ(2));

  mrb_value self = mrb_obj_value(o);
  {
    TopoDS_Shape* shape = siren_shape_get(mrb, self);
    TopoDS_Edge edge = TopoDS::Edge(*shape);
    Standard_Real first, last;
    opencascade::handle<Geom_Curve> hgcurve = BRep_Tool::Curve(edge, first, last);
    mrb_obj_iv_set(mrb, o, mrb_intern_lit(mrb, "@curve"), siren_curve_new(mrb, &hgcurve));
    mrb_define_singleton_method(mrb, o, "curve", siren_edge_curve, MRB_ARGS_NONE());
  }
  mrb_define_singleton_method(mrb, o, "terms", siren_edge_terms, MRB_ARGS_NONE());

  mrb_define_singleton_method(mrb, o, "length", siren_edge_length, MRB_ARGS_NONE());

  return;
}

mrb_value siren_edge_sp(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* c = siren_shape_get(mrb, self);
  BRepAdaptor_Curve bracurve(TopoDS::Edge(*c));
  gp_Pnt sp = bracurve.Value(bracurve.FirstParameter());
  return siren_pnt_to_ary(mrb, sp);
}

mrb_value siren_edge_tp(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* c = siren_shape_get(mrb, self);
  BRepAdaptor_Curve bracurve(TopoDS::Edge(*c));
  gp_Pnt tp = bracurve.Value(bracurve.LastParameter());
  return siren_pnt_to_ary(mrb, tp);
}

mrb_value siren_edge_to_pts(mrb_state* mrb, mrb_value self)
{
  mrb_float deflect;
  int argc = mrb_get_args(mrb, "|f", &deflect);

  TopoDS_Shape* shape = siren_shape_get(mrb, self);

  if (argc != 1) {
    deflect = 1.0e-1;
  }
  TopoDS_Edge edge = TopoDS::Edge(*shape);
  BRepAdaptor_Curve adaptor(edge);
  double first_param, last_param;
  first_param = adaptor.FirstParameter();
  last_param = adaptor.LastParameter();

  mrb_value line = mrb_ary_new(mrb);

  GCPnts_UniformDeflection unidef(adaptor, deflect);
  if (unidef.IsDone()) {
    // first point
    gp_Pnt p = adaptor.Value(first_param);
    mrb_ary_push(mrb, line, siren_pnt_to_ary(mrb, p));
    gp_Pnt prev = p;

    for (int i=1; i<=unidef.NbPoints(); i++) {
      p = unidef.Value(i);
      if (prev.IsEqual(p, 1.0e-7)) {
        continue;
      }
      mrb_ary_push(mrb, line, siren_pnt_to_ary(mrb, p));
      prev = p;
    }
    // last point
    p = adaptor.Value(last_param);
    if (!prev.IsEqual(p, 1.0e-7)) {
      mrb_ary_push(mrb, line, siren_pnt_to_ary(mrb, p));
    }
  }
  return line;
}

mrb_value siren_edge_param(mrb_state* mrb, mrb_value self)
{
  mrb_value xyz;
  mrb_float tol = 1.0e-7;
  int argc = mrb_get_args(mrb, "A|f", &xyz, &tol);

  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  TopoDS_Edge edge = TopoDS::Edge(*shape);

  ShapeAnalysis_Curve ana;
  BRepAdaptor_Curve gcurve(edge);
  gp_Pnt p = siren_ary_to_pnt(mrb, xyz);
  gp_Pnt pp;
  Standard_Real param;
  Standard_Real distance = ana.Project(gcurve, p, tol, pp, param);

  if (fabs(distance) > tol) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Specified position is not on the edge.");
  }

  return mrb_float_value(mrb, param);
}

mrb_value siren_edge_to_xyz(mrb_state* mrb, mrb_value self)
{
  mrb_float param;
  int argc = mrb_get_args(mrb, "f", &param);
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  BRepAdaptor_Curve C(TopoDS::Edge(*shape));
  gp_Pnt p;
  gp_Vec v1, v2;
  C.D2(param, p, v1, v2);
  return siren_pnt_to_ary(mrb, p);
}

mrb_value siren_edge_curvature(mrb_state* mrb, mrb_value self)
{
  mrb_float param;
  int argc = mrb_get_args(mrb, "f", &param);
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  BRepAdaptor_Curve C(TopoDS::Edge(*shape));
  gp_Pnt p;
  gp_Vec v1, v2;
  C.D2(param, p, v1, v2);
  return siren_vec_new(mrb, v2.X(), v2.Y(), v2.Z());
}

mrb_value siren_edge_tangent(mrb_state* mrb, mrb_value self)
{
  mrb_float param;
  int argc = mrb_get_args(mrb, "f", &param);
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  BRepAdaptor_Curve C(TopoDS::Edge(*shape));
  gp_Pnt p;
  gp_Vec v1, v2;
  C.D2(param, p, v1, v2);
  return siren_vec_new(mrb, v1.X(), v1.Y(), v1.Z());
}

mrb_value siren_edge_nurbs_def(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  TopoDS_Edge edge = TopoDS::Edge(*shape);
  Standard_Real first, last;
  opencascade::handle<Geom_Curve> hgcurve = BRep_Tool::Curve(edge, first, last);
#if 0
  opencascade::handle<Geom_TrimmedCurve> hgtc = new Geom_TrimmedCurve(hgcurve, first, last);
  opencascade::handle<Geom_BSplineCurve> hgbc = opencascade::handle<Geom_BSplineCurve>::DownCast(hgtc->BasisCurve());
#else
  opencascade::handle<Geom_BSplineCurve> hgbc = opencascade::handle<Geom_BSplineCurve>::DownCast(hgcurve);
#endif
  if (hgbc.IsNull()) {
    // Failed to downcast to BSplineCurve
    return mrb_nil_value();
  }
  mrb_value res = mrb_ary_new(mrb);
  // degree
  mrb_ary_push(mrb, res, mrb_fixnum_value((int)hgbc->Degree()));
  // knots
  mrb_value knots = mrb_ary_new(mrb);
  for (int i=1; i <= hgbc->NbKnots(); i++) {
    mrb_ary_push(mrb, knots, mrb_float_value(mrb, hgbc->Knot(i)));
  }
  mrb_ary_push(mrb, res, knots);
  // mults
  mrb_value mults = mrb_ary_new(mrb);
  for (int i=1; i <= hgbc->NbKnots(); i++) {
    mrb_ary_push(mrb, mults, mrb_fixnum_value(hgbc->Multiplicity(i)));
  }
  mrb_ary_push(mrb, res, mults);
  // poles
  mrb_value poles = mrb_ary_new(mrb);
  for (int i=1; i <= hgbc->NbPoles(); i++) {
    mrb_ary_push(mrb, poles, siren_vec_new(mrb, hgbc->Pole(i).X(), hgbc->Pole(i).Y(), hgbc->Pole(i).Z()));
  }
  mrb_ary_push(mrb, res, poles);
  // weights
  mrb_value weights = mrb_ary_new(mrb);
  for (int i=1; i <= hgbc->NbPoles(); i++) {
    mrb_ary_push(mrb, weights, mrb_float_value(mrb, hgbc->Weight(i)));
  }
  mrb_ary_push(mrb, res, weights);
  // params
  mrb_ary_push(mrb, res, mrb_float_value(mrb, first));
  mrb_ary_push(mrb, res, mrb_float_value(mrb, last));
  return res;
}

mrb_value siren_edge_terms(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  TopoDS_Edge edge = TopoDS::Edge(*shape);
  Standard_Real first, last;
  BRep_Tool::Curve(edge, first, last);
  mrb_value res = mrb_ary_new(mrb);
  mrb_ary_push(mrb, res, mrb_float_value(mrb, first));
  mrb_ary_push(mrb, res, mrb_float_value(mrb, last));
  return res;
}

mrb_value siren_edge_curve(mrb_state* mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@curve"));
}

mrb_value siren_edge_extrema(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  TopoDS_Shape* s = siren_shape_get(mrb, other);
  TopoDS_Edge e2 = TopoDS::Edge(*s);
  if (e2.IsNull()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Specified shape type is not edge.");
  }
  TopoDS_Edge e1 = TopoDS::Edge(*siren_shape_get(mrb, self));
  BRepExtrema_ExtCC ext(e1, e2);
  if (!ext.IsDone()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Failed to get extrema points.");
  }
  else if (ext.IsParallel()) {
    return mrb_nil_value();
  }
  mrb_value p1s = mrb_ary_new(mrb);
  mrb_value p2s = mrb_ary_new(mrb);
  for (int i = 1; i <= ext.NbExt(); i++) {
    mrb_ary_push(mrb, p1s, mrb_float_value(mrb, ext.ParameterOnE1(i)));
    mrb_ary_push(mrb, p2s, mrb_float_value(mrb, ext.ParameterOnE2(i)));
  }
  mrb_value res[2] = { p1s, p2s };
  return mrb_ary_new_from_values(mrb, 2, res);
}

mrb_value siren_edge_split(mrb_state* mrb, mrb_value self)
{
  mrb_float param;
  int argc = mrb_get_args(mrb, "f", &param);
  Standard_Real first, last;
  TopoDS_Shape* s = siren_shape_get(mrb, self);
  TopoDS_Edge e = TopoDS::Edge(*s);
  opencascade::handle<Geom_Curve> gc  = BRep_Tool::Curve(e, first, last);
  if (param <= first || param >= last) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Specified parameter is out of range of curve parameter.");
  }
  TopoDS_Edge e1 = BRepBuilderAPI_MakeEdge(gc, first, param);
  TopoDS_Edge e2 = BRepBuilderAPI_MakeEdge(gc, param, last);
  mrb_value res[] = { siren_shape_new(mrb, e1), siren_shape_new(mrb, e2) };
  return mrb_ary_new_from_values(mrb, 2, res);
}

mrb_value siren_edge_trim(mrb_state* mrb, mrb_value self)
{
  mrb_float first2, last2;
  int argc = mrb_get_args(mrb, "ff", &first2, &last2);
  if (first2 == last2) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Specified parameter has same value.");
  }
  Standard_Real first, last;
  TopoDS_Shape* s = siren_shape_get(mrb, self);
  TopoDS_Edge e = TopoDS::Edge(*s);
  opencascade::handle<Geom_Curve> gc  = BRep_Tool::Curve(e, first, last);
  TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(gc, first2, last2);
  return siren_shape_new(mrb, edge);
}

mrb_value siren_edge_length(mrb_state* mrb, mrb_value self)
{
  Standard_Real res = 0.0;
  mrb_value ary = siren_edge_to_pts(mrb, self);
  gp_Pnt prev;
  for (int i=0; i < mrb_ary_len(mrb, ary); i++) {
    if (i == 0) {
      prev = siren_ary_to_pnt(mrb, mrb_ary_ref(mrb, ary, i));
    }
    else {
      gp_Pnt curr = siren_ary_to_pnt(mrb, mrb_ary_ref(mrb, ary, i));
      res += curr.Distance(prev);
      prev = curr;
    }
  }
  return mrb_float_value(mrb, res);
}

