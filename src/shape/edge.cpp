#include "shape/edge.h"

mrb_value siren_edge_new(mrb_state* mrb, const TopoDS_Shape* src)
{
  mrb_value obj;
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Edge")));
  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = *src; // Copy to inner native member
  DATA_PTR(obj)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(obj) = &siren_edge_type;
  return obj;
}

TopoDS_Edge siren_edge_get(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, self, &siren_edge_type));
  TopoDS_Edge edge = TopoDS::Edge(*shape);
  if (edge.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Edge."); }
  return edge;
}

bool siren_edge_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* cls_edge = mrb_define_class_under(mrb, mod_siren, "Edge", cls_shape);
  MRB_SET_INSTANCE_TT(cls_edge, MRB_TT_DATA);
  mrb_define_method(mrb, cls_edge, "initialize", siren_shape_init,     MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_edge, "sp",         siren_edge_sp,        MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_edge, "tp",         siren_edge_tp,        MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_edge, "to_pts",     siren_edge_to_pts,    MRB_ARGS_OPT(1));
  mrb_define_method(mrb, cls_edge, "param",      siren_edge_param,     MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_method(mrb, cls_edge, "to_xyz",     siren_edge_to_xyz,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_edge, "curvature",  siren_edge_curvature, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_edge, "tangent",    siren_edge_tangent,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_edge, "extrema",    siren_edge_extrema,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_edge, "split",      siren_edge_split,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_edge, "trim",       siren_edge_trim,      MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_edge, "terms",      siren_edge_terms,     MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_edge, "length",     siren_edge_length,    MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_edge, "curve",      siren_edge_curve,     MRB_ARGS_NONE());
  return true;
}

struct RClass* siren_edge_rclass(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Edge")));
}

mrb_value siren_edge_sp(mrb_state* mrb, mrb_value self)
{
  BRepAdaptor_Curve bracurve(siren_edge_get(mrb, self));
  gp_Pnt sp = bracurve.Value(bracurve.FirstParameter());
  return siren_pnt_to_ary(mrb, sp);
}

mrb_value siren_edge_tp(mrb_state* mrb, mrb_value self)
{
  BRepAdaptor_Curve bracurve(siren_edge_get(mrb, self));
  gp_Pnt tp = bracurve.Value(bracurve.LastParameter());
  return siren_pnt_to_ary(mrb, tp);
}

mrb_value siren_edge_to_pts(mrb_state* mrb, mrb_value self)
{
  mrb_float deflect;
  int argc = mrb_get_args(mrb, "|f", &deflect);
  if (argc != 1) {
    deflect = 1.0e-1;
  }
  TopoDS_Edge edge = siren_edge_get(mrb, self);
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

  TopoDS_Edge edge = siren_edge_get(mrb, self);

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
  BRepAdaptor_Curve C(siren_edge_get(mrb, self));
  gp_Pnt p;
  gp_Vec v1, v2;
  C.D2(param, p, v1, v2);
  return siren_pnt_to_ary(mrb, p);
}

mrb_value siren_edge_curvature(mrb_state* mrb, mrb_value self)
{
  mrb_float param;
  int argc = mrb_get_args(mrb, "f", &param);
  BRepAdaptor_Curve C(siren_edge_get(mrb, self));
  gp_Pnt p;
  gp_Vec v1, v2;
  C.D2(param, p, v1, v2);
  return siren_vec_new(mrb, v2.X(), v2.Y(), v2.Z());
}

mrb_value siren_edge_tangent(mrb_state* mrb, mrb_value self)
{
  mrb_float param;
  int argc = mrb_get_args(mrb, "f", &param);
  BRepAdaptor_Curve C(siren_edge_get(mrb, self));
  gp_Pnt p;
  gp_Vec v1, v2;
  C.D2(param, p, v1, v2);
  return siren_vec_new(mrb, v1.X(), v1.Y(), v1.Z());
}

mrb_value siren_edge_terms(mrb_state* mrb, mrb_value self)
{
  TopoDS_Edge edge = siren_edge_get(mrb, self);
  Standard_Real first, last;
  BRep_Tool::Curve(edge, first, last);
  mrb_value res = mrb_ary_new(mrb);
  mrb_ary_push(mrb, res, mrb_float_value(mrb, first));
  mrb_ary_push(mrb, res, mrb_float_value(mrb, last));
  return res;
}

mrb_value siren_edge_curve(mrb_state* mrb, mrb_value self)
{
  TopoDS_Edge edge = siren_edge_get(mrb, self);
  // // set property
  // Standard_Real first, last;
  // handle<Geom_Curve> hgcurve = BRep_Tool::Curve(edge, first, last);
  // mrb_obj_iv_set(mrb, mrb_obj_value(cls_edge), mrb_intern_lit(mrb, "@curve"), siren_curve_new(mrb, &hgcurve));
  // // get property
  // return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@curve"));
  Standard_Real first, last;
  handle<Geom_Curve> hgcurve = BRep_Tool::Curve(edge, first, last);
  return siren_curve_new(mrb, &hgcurve);
}

mrb_value siren_edge_extrema(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  TopoDS_Edge e2 = siren_edge_get(mrb, other);
  if (e2.IsNull()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Specified shape type is not edge.");
  }
  TopoDS_Edge e1 = siren_edge_get(mrb, self);
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
  TopoDS_Edge e = siren_edge_get(mrb, self);
  handle<Geom_Curve> gc  = BRep_Tool::Curve(e, first, last);
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
  TopoDS_Edge e = siren_edge_get(mrb, self);
  handle<Geom_Curve> gc  = BRep_Tool::Curve(e, first, last);
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

mrb_value siren_edge_obj(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Edge"));
}
