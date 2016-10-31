#include "shape/wire.h"

mrb_value siren_wire_new(mrb_state* mrb, const TopoDS_Shape* src)
{
  mrb_value obj;
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Wire")));
  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = *src; // Copy to inner native member
  DATA_PTR(obj)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(obj) = &siren_wire_type;
  return obj;
}

TopoDS_Wire siren_wire_get(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, self, &siren_wire_type));
  TopoDS_Wire wire = TopoDS::Wire(*shape);
  if (wire.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Wire."); }
  return wire;
}

bool siren_wire_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* cls_wire = mrb_define_class_under(mrb, mod_siren, "Wire", cls_shape);
  MRB_SET_INSTANCE_TT(cls_wire, MRB_TT_DATA);
  mrb_define_method(mrb, cls_wire, "initialize",    siren_shape_init,         MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_wire, "ordered_edges", siren_wire_ordered_edges, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_wire, "curves",        siren_wire_curves,        MRB_ARGS_NONE());
  return true;
}

struct RClass* siren_wire_rclass(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Wire")));
}

mrb_value siren_wire_ordered_edges(mrb_state* mrb, mrb_value self)
{
  TopoDS_Wire wire = siren_wire_get(mrb, self);
  mrb_value res = mrb_ary_new(mrb);
  for (BRepTools_WireExplorer exp(wire); exp.More(); exp.Next()) {
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

