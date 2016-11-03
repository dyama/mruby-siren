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

  auto obj_wire = mrb_obj_ptr(siren_wire_obj(mrb));
  mrb_define_singleton_method(mrb, obj_wire, "make", siren_wire_make, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_singleton_method(mrb, obj_wire, "join", siren_wire_make, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
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

mrb_value siren_wire_obj(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Wire"));
}

mrb_value siren_wire_make(mrb_state* mrb, mrb_value self)
{
  mrb_value objs;
  mrb_float tol;
  int argc = mrb_get_args(mrb, "A|f", &objs, &tol);
  BRepBuilderAPI_MakeWire api;
#ifdef USE_WIRE_FIX
  ShapeFix_Wire sfw;
  handle<ShapeExtend_WireData> wd = new ShapeExtend_WireData();
  ShapeFix_ShapeTolerance FTol;
  int osize = mrb_ary_len(mrb, objs);
  for (int i = 0; i < osize ; i++) {
    mrb_value obj = mrb_ary_ref(mrb, objs, i);
    TopoDS_Shape* s = siren_shape_get(mrb, obj);
    if (s->IsNull()) {
      continue;
    }
    TopExp_Explorer exp(*s, TopAbs_EDGE);
    for (; exp.More(); exp.Next()) {
      wd->Add(TopoDS::Edge(exp.Current()));
    }
  }
  if (wd->NbEdges() == 0) {
    return mrb_nil_value();
  }
  sfw.Load(wd);
  sfw.Perform();
  for (int i = 1; i <= sfw.NbEdges(); i ++) {
    TopoDS_Edge e = sfw.WireData()->Edge(i);
    FTol.SetTolerance(e, argc == 1 ? 0.01 : tol, TopAbs_VERTEX);
    api.Add(e);
  }
  return siren_shape_new(mrb, api.Shape());
#else
  ShapeFix_ShapeTolerance fixtol;
  bool has_tol = argc == 2;
  for (int i = 0; i < mrb_ary_len(mrb, objs); i++) {
    TopoDS_Shape* shape = siren_shape_get(mrb, mrb_ary_ref(mrb, objs, i));
    if (shape->ShapeType() == TopAbs_EDGE) {
      if (has_tol) {
        fixtol.SetTolerance(*shape, tol, TopAbs_VERTEX);
      }
      api.Add(TopoDS::Edge(*shape));
    }
    else if (shape->ShapeType() == TopAbs_WIRE) {
      if (has_tol) {
        fixtol.SetTolerance(*shape, tol, TopAbs_VERTEX);
        fixtol.SetTolerance(*shape, tol, TopAbs_EDGE);
      }
      api.Add(TopoDS::Wire(*shape));
    }
  }
  api.Build();
  if (!api.IsDone()) {
    switch (api.Error()) {
      case BRepBuilderAPI_EmptyWire:
        mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a wire. (Empty wire)");
        break;
      case BRepBuilderAPI_DisconnectedWire:
        mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a wire. (Disconnected wire)");
        break;
      case BRepBuilderAPI_NonManifoldWire:
        mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a wire. (Non manifold wire)");
        break;
      default: break;
    }
  }
#endif
  return siren_wire_new(mrb, &api.Wire());
}
