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
  mrb_define_method(mrb, cls_vertex, "initialize", siren_vertex_init, MRB_ARGS_NONE());
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

mrb_value siren_vertex_init(mrb_state* mrb, mrb_value self)
{
  mrb_value* a;
  mrb_int len;
  int argc = mrb_get_args(mrb, "*", &a, &len);

  Standard_Real x = 0.0, y = 0.0, z = 0.0;
  if (mrb_array_p(a[0])) {
    gp_Pnt p = siren_ary_to_pnt(mrb, a[0]);
    x = p.X(); y = p.Y(); z = p.Z();
  }
  else {
    if (len >= 1) {
      if (mrb_fixnum_p(a[0]))
        x = mrb_fixnum(a[0]);
      else if mrb_float_p(a[0])
        x = mrb_float(a[0]);
    }
    if (len >= 2) {
      if (mrb_fixnum_p(a[1]))
        y = mrb_fixnum(a[1]);
      else if (mrb_float_p(a[1]))
        y = mrb_float(a[1]);
    }
    if (len >= 3) {
      if (mrb_fixnum_p(a[2]))
        z = mrb_fixnum(a[2]);
      else if (mrb_float_p(a[2]))
        z = mrb_float(a[2]);
    }
  }
  TopoDS_Vertex v = BRepBuilderAPI_MakeVertex(gp_Pnt(x, y, z));

  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = v; // Copy to inner native member
  DATA_PTR(self)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(self) = &siren_vertex_type;
  return self;
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

mrb_value siren_vertex_obj(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Vertex"));
}

