#include "curve.h"

bool siren_curve_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Curve");
  mrb_define_class_method(mrb, rclass, "endpts", siren_curve_endpts, ARGS_REQ(1));
  return true;
}

mrb_value siren_curve_endpts(mrb_state* mrb, mrb_value self)
{
  mrb_value curve;
  int argc = mrb_get_args(mrb, "o", &curve);

  mrb_value res = mrb_ary_new(mrb);

  TopoDS_Shape* c = siren_shape_get(mrb, curve);
  TopExp_Explorer ex(*c, TopAbs_EDGE);

  for (; ex.More(); ex.Next()) {
    BRepAdaptor_Curve bracurve(TopoDS::Edge(ex.Current()));
    gp_Pnt sp = bracurve.Value(bracurve.FirstParameter());
    gp_Pnt tp = bracurve.Value(bracurve.LastParameter());
    mrb_value m_sp = siren_vec_new(mrb, sp.X(), sp.Y(), sp.Z());
    mrb_value m_tp = siren_vec_new(mrb, tp.X(), tp.Y(), tp.Z());
    mrb_value ar = mrb_ary_new(mrb);
    mrb_ary_push(mrb, ar, m_sp);
    mrb_ary_push(mrb, ar, m_tp);
    mrb_ary_push(mrb, res, ar);
  }

  return res;
}


