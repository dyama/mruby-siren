#include "shape/wire.h"

void siren_wire_install(mrb_state* mrb, RObject* o)
{
  mrb_define_singleton_method(mrb, o, "ordered_edges", siren_wire_ordered_edges, MRB_ARGS_NONE());
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

