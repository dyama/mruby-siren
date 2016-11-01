#include "shape/solid.h"

mrb_value siren_solid_new(mrb_state* mrb, const TopoDS_Shape* src)
{
  mrb_value obj;
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Solid")));
  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = *src; // Copy to inner native member
  DATA_PTR(obj)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(obj) = &siren_solid_type;
  return obj;
}

TopoDS_Solid siren_solid_get(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, self, &siren_solid_type));
  TopoDS_Solid solid = TopoDS::Solid(*shape);
  if (solid.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Solid."); }
  return solid;
}

bool siren_solid_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* cls_solid = mrb_define_class_under(mrb, mod_siren, "Solid", cls_shape);
  MRB_SET_INSTANCE_TT(cls_solid, MRB_TT_DATA);
  mrb_define_method(mrb, cls_solid, "initialize", siren_solid_init,  MRB_ARGS_NONE());
  return true;
}

struct RClass* siren_solid_rclass(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Solid")));
}

mrb_value siren_solid_obj(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Solid"));
}

mrb_value siren_solid_init(mrb_state* mrb, mrb_value self)
{
  mrb_value* a;
  mrb_int len;
  int argc = mrb_get_args(mrb, "*", &a, &len);

  BRepBuilderAPI_MakeSolid solid_maker;
  for (int i = 0; i < len; i++) {
    TopoDS_Shell shell = siren_shell_get(mrb, a[i]);
    solid_maker.Add(shell);
  }
  if (!solid_maker.IsDone()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Failed to make a Solid.");
  }
  TopoDS_Shape shape = solid_maker.Shape();

  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = shape; // Copy to inner native member
  DATA_PTR(self)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(self) = &siren_solid_type;
  return self;
}

