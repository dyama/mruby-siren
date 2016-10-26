#include "shape/wire.h"

void siren_wire_install(mrb_state* mrb, RObject* o)
{
  mrb_define_singleton_method(mrb, o, "ordered_edges", siren_wire_ordered_edges, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "curves",        siren_wire_curves, MRB_ARGS_NONE());
  return;
}

mrb_value siren_wire_ordered_edges(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* s = siren_shape_get(mrb, self);
  TopoDS_Wire w = TopoDS::Wire(*s);
  mrb_value res = mrb_ary_new(mrb);
  for (BRepTools_WireExplorer exp(w); exp.More(); exp.Next()) {
    TopoDS_Edge e = exp.Current();
    mrb_ary_push(mrb, res, siren_shape_new(mrb, e));
  }
  return res;
}

mrb_value siren_wire_curves(mrb_state* mrb, mrb_value self)
{
  mrb_value res = mrb_ary_new(mrb);
  mrb_value edges = mrb_funcall(mrb, self, "edges", 0);
  for (int i = 0; i < mrb_ary_len(mrb, edges); i++) {
    mrb_value edge = mrb_ary_ref(mrb, edges, i);
    mrb_value curve = mrb_funcall(mrb, edge, "curve", 0);
    mrb_ary_push(mrb, res, curve);
  }
  return res;
}

