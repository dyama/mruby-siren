#include "shape/compound.h"

mrb_value siren_compound_new(mrb_state* mrb, const TopoDS_Shape* src)
{
  mrb_value obj;
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Compound")));
  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = *src; // Copy to inner native member
  DATA_PTR(obj)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(obj) = &siren_compound_type;
  return obj;
}

TopoDS_Compound siren_compound_get(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, self, &siren_compound_type));
  TopoDS_Compound compound = TopoDS::Compound(*shape);
  if (compound.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Compound."); }
  return compound;
}

bool siren_compound_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* cls_compound = mrb_define_class_under(mrb, mod_siren, "Compound", cls_shape);
  MRB_SET_INSTANCE_TT(cls_compound, MRB_TT_DATA);
  mrb_define_method(mrb, cls_compound, "initialize", siren_shape_init,  MRB_ARGS_NONE());
  return true;
}

struct RClass* siren_compound_rclass(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Compound")));
}

mrb_value siren_compound_obj(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Compound"));
}

