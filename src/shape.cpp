#include "shape.h"

bool mrb_siren_shape_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Shape", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", mrb_method_name(shape_init),      ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_s",       mrb_method_name(shape_to_s),      ARGS_NONE());
  mrb_define_method(mrb, rclass, "null?",      mrb_method_name(shape_is_null),   ARGS_NONE());
  mrb_define_method(mrb, rclass, "shapetype",  mrb_method_name(shape_shapetype), ARGS_NONE());
  mrb_define_method(mrb, rclass, "location",   mrb_method_name(shape_location), ARGS_NONE());

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
  DATA_TYPE(self) = &mrb_siren_shape_type;
  return self;
}

void mrb_siren_shape_final(mrb_state* mrb, void* p)
{
  TopoDS_Shape* s = static_cast<TopoDS_Shape*>(p);
  s->Nullify();
}

mrb_method(shape_to_s)
{
  TopoDS_Shape* shape = mrb_siren_get_shape(mrb, self);
  return mrb_str_new_cstr(mrb, "#Shape<>");
}

mrb_method(shape_is_null)
{
  TopoDS_Shape* shape = mrb_siren_get_shape(mrb, self);
  return shape->IsNull() ? mrb_true_value() : mrb_false_value();
}

mrb_method(shape_shapetype)
{
  TopoDS_Shape* shape = mrb_siren_get_shape(mrb, self);
  int type = (int)shape->ShapeType();
  return mrb_fixnum_value(type);
}

mrb_method(shape_location)
{
  TopoDS_Shape* shape = mrb_siren_get_shape(mrb, self);
  gp_XYZ pos = shape->Location().Transformation().TranslationPart();
  mrb_value args[3];
  args[0] = mrb_float_value(mrb, pos.X());
  args[1] = mrb_float_value(mrb, pos.Y());
  args[2] = mrb_float_value(mrb, pos.Z());
  return mrb_class_new_instance(mrb, 3, args, mrb_class_get(mrb, "Vec"));
}

TopoDS_Shape* mrb_siren_get_shape(mrb_state* mrb, mrb_value obj)
{
  return static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, obj, &mrb_siren_shape_type));
}

