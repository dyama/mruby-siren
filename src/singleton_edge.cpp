#include "singleton_edge.h"

void siren_edge_install(mrb_state* mrb, RObject* o)
{
  mrb_define_singleton_method(mrb, o, "sp",     siren_edge_sp,     MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "tp",     siren_edge_tp,     MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "to_pts", siren_edge_to_pts, MRB_ARGS_OPT(1));
  return;
}

mrb_value siren_edge_sp(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* c = siren_shape_get(mrb, self);
  BRepAdaptor_Curve bracurve(TopoDS::Edge(*c));
  gp_Pnt sp = bracurve.Value(bracurve.FirstParameter());
  return siren_vec_new(mrb, sp.X(), sp.Y(), sp.Z());
}

mrb_value siren_edge_tp(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* c = siren_shape_get(mrb, self);
  BRepAdaptor_Curve bracurve(TopoDS::Edge(*c));
  gp_Pnt tp = bracurve.Value(bracurve.LastParameter());
  return siren_vec_new(mrb, tp.X(), tp.Y(), tp.Z());
}

mrb_value siren_edge_to_pts(mrb_state* mrb, mrb_value self)
{
  mrb_float deflect;
  int argc = mrb_get_args(mrb, "|f", &deflect);

  TopoDS_Shape* shape = siren_shape_get(mrb, self);

  if (argc != 2) {
    deflect = 1.0e-1;
  }

  mrb_value result = mrb_ary_new(mrb);
  double first_param, last_param;

  TopExp_Explorer exp(*shape, TopAbs_EDGE);
  for(; exp.More(); exp.Next()) {
    TopoDS_Edge edge = TopoDS::Edge(exp.Current());

    BRepAdaptor_Curve adaptor(edge);
    first_param = adaptor.FirstParameter();
    last_param = adaptor.LastParameter();

    GCPnts_UniformDeflection unidef(adaptor, (Standard_Real)deflect);
    if (!unidef.IsDone()) {
      continue;
    }

    mrb_value line = mrb_ary_new(mrb);

    // first point
    gp_Pnt p = adaptor.Value(first_param);
    mrb_ary_push(mrb, line, siren_vec_new(mrb, p.X(), p.Y(), p.Z()));

    for (int i=1; i<=unidef.NbPoints(); i++) {
      p = unidef.Value(i);
      mrb_ary_push(mrb, line, siren_vec_new(mrb, p.X(), p.Y(), p.Z()));
    }

    // last point
    p = adaptor.Value(last_param);
    mrb_ary_push(mrb, line, siren_vec_new(mrb, p.X(), p.Y(), p.Z()));

    mrb_ary_push(mrb, result, line);
  }

  return result;
}

