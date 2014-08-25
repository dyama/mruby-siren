#include "shape.h"

mrb_data_type* mrb_siren_get_shape_type(void)
{
  return &mrb_siren_shape_type;
}

bool mrb_siren_shape_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Shape", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", mrb_method_name(shape_init),      ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_s",       mrb_method_name(shape_to_s),      ARGS_NONE());
  mrb_define_method(mrb, rclass, "null?",      mrb_method_name(shape_is_null),   ARGS_NONE());
  mrb_define_method(mrb, rclass, "shapetype",  mrb_method_name(shape_shapetype), ARGS_NONE());

  // mrb_define_method(mrb, rclass, "copy", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "translate", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "rotate", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "scale", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "move", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "translate!", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "rotate!", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "scale!", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "move!", mrb_method_dummy, ARGS_NONE());

  return true;
}

mrb_method(shape_init)
{
  TopoDS_Shape* shape = new TopoDS_Shape();
  DATA_PTR(self) = shape;
  DATA_TYPE(self) = mrb_siren_get_shape_type();
  return self;
}

void mrb_siren_shape_final(mrb_state* mrb, void* p)
{
  TopoDS_Shape* s = static_cast<TopoDS_Shape*>(p);
  s->Nullify();
}

mrb_method(shape_to_s)
{
  void* p = mrb_get_datatype(mrb, self, mrb_siren_get_shape_type());
  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(p);
  return mrb_str_new_cstr(mrb, "#Shape<>");
}

mrb_method(shape_is_null)
{
  void* p = mrb_get_datatype(mrb, self, mrb_siren_get_shape_type());
  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(p);
  return shape->IsNull() ? mrb_true_value() : mrb_false_value();
}

mrb_method(shape_shapetype)
{
  void* p = mrb_get_datatype(mrb, self, mrb_siren_get_shape_type());
  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(p);
  int type = (int)shape->ShapeType();
  return mrb_fixnum_value(type);
}

