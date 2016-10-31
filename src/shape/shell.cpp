#include "shape/shell.h"

mrb_value siren_shell_new(mrb_state* mrb, const TopoDS_Shape* src)
{
  mrb_value obj;
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Shell")));
  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = *src; // Copy to inner native member
  DATA_PTR(obj)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(obj) = &siren_shell_type;
  return obj;
}

TopoDS_Shell siren_shell_get(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, self, &siren_shell_type));
  TopoDS_Shell shell = TopoDS::Shell(*shape);
  if (shell.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Shell."); }
  return shell;
}

bool siren_shell_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* cls_shell = mrb_define_class_under(mrb, mod_siren, "Shell", cls_shape);
  MRB_SET_INSTANCE_TT(cls_shell, MRB_TT_DATA);
  mrb_define_method(mrb, cls_shell, "initialize", siren_shape_init,  MRB_ARGS_NONE());
  return true;
}

struct RClass* siren_shell_rclass(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Shell")));
}

