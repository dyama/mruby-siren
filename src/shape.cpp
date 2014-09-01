#include "shape.h"

mrb_value siren_shape_new(mrb_state* mrb, const TopoDS_Shape* shape)
{
  mrb_value res = mrb_class_new_instance(mrb, 0, NULL, mrb_class_get(mrb, "Shape"));
  DATA_PTR(res) = const_cast<TopoDS_Shape*>(shape);
  return res;
}

bool siren_shape_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Shape", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", siren_shape_init,      ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_s",       siren_shape_to_s,      ARGS_NONE());
  mrb_define_method(mrb, rclass, "null?",      siren_shape_is_null,   ARGS_NONE());
  mrb_define_method(mrb, rclass, "shapetype",  siren_shape_shapetype, ARGS_NONE());
  mrb_define_method(mrb, rclass, "location",   siren_shape_location,  ARGS_NONE());

  mrb_define_method(mrb, rclass, "translate", siren_shape_translate,  ARGS_REQ(1));
  // mrb_define_method(mrb, rclass, "copy", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "rotate", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "scale", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "move", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "translate!", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "rotate!", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "scale!", mrb_method_dummy, ARGS_NONE());
  // mrb_define_method(mrb, rclass, "move!", mrb_method_dummy, ARGS_NONE());

  return true;
}

mrb_value siren_shape_init(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = new TopoDS_Shape();
  DATA_PTR(self) = shape;
  DATA_TYPE(self) = &siren_shape_type;
  return self;
}

void siren_shape_final(mrb_state* mrb, void* p)
{
  TopoDS_Shape* s = static_cast<TopoDS_Shape*>(p);
  s->Nullify();
}

mrb_value siren_shape_to_s(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  return mrb_str_new_cstr(mrb, "#Shape<>");
}

mrb_value siren_shape_is_null(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  return shape->IsNull() ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_shape_shapetype(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  int type = (int)shape->ShapeType();
  return mrb_fixnum_value(type);
}

mrb_value siren_shape_location(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  gp_XYZ pos = shape->Location().Transformation().TranslationPart();
  return siren_vec_new(mrb, pos.X(), pos.Y(), pos.Z());
}

TopoDS_Shape* siren_shape_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, obj, &siren_shape_type));
}

mrb_value siren_shape_translate(mrb_state* mrb, mrb_value self)
{
  mrb_value vec;
  int argc = mrb_get_args(mrb, "o", &vec);

  gp_Vec* _vec = siren_vec_get(mrb, vec);
  gp_Trsf trsf;
  trsf.SetTranslation(*_vec);

  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  shape->Move(trsf);

  return mrb_nil_value();
}

