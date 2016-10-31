#include "shape/vertex.h"

mrb_value siren_vertex_new(mrb_state* mrb, const TopoDS_Shape* src)
{
  mrb_value obj;
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Vertex")));
  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = *src; // Copy to inner native member
  DATA_PTR(obj)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(obj) = &siren_vertex_type;
  return obj;
}

TopoDS_Vertex siren_vertex_get(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, self, &siren_vertex_type));
  TopoDS_Vertex vertex = TopoDS::Vertex(*shape);
  if (vertex.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Vertex."); }
  return vertex;
}

bool siren_vertex_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* cls_vertex = mrb_define_class_under(mrb, mod_siren, "Vertex", cls_shape);
  MRB_SET_INSTANCE_TT(cls_vertex, MRB_TT_DATA);
  mrb_define_method(mrb, cls_vertex, "initialize", siren_shape_init,  MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vertex, "xyz",        siren_vertex_xyz,  MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vertex, "to_a",       siren_vertex_xyz,  MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vertex, "to_v",       siren_vertex_to_v, MRB_ARGS_NONE());
  return true;
}

struct RClass* siren_vertex_rclass(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Vertex")));
}

mrb_value siren_vertex_xyz(mrb_state* mrb, mrb_value self)
{
  TopoDS_Vertex vertex = siren_vertex_get(mrb, self);
  return siren_pnt_to_ary(mrb, BRep_Tool::Pnt(vertex));
}

mrb_value siren_vertex_to_v(mrb_state* mrb, mrb_value self)
{
  TopoDS_Vertex vertex = siren_vertex_get(mrb, self);
  gp_Pnt p = BRep_Tool::Pnt(vertex);
  return siren_vec_new(mrb, p.X(), p.Y(), p.Z());
}

