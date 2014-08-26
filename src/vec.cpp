#include "vec.h"

bool siren_vec_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Vec", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", mrb_method_name(vec_init),   ARGS_NONE() | ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "to_s",       mrb_method_name(vec_to_s),   ARGS_NONE());
  mrb_define_method(mrb, rclass, "x",          mrb_method_name(vec_x),      ARGS_NONE());
  mrb_define_method(mrb, rclass, "y",          mrb_method_name(vec_y),      ARGS_NONE());
  mrb_define_method(mrb, rclass, "z",          mrb_method_name(vec_z),      ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_a",       mrb_method_name(vec_to_a),   ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_xyz",     mrb_method_name(vec_to_xyz), ARGS_NONE());
  return true;
}

mrb_method(vec_init)
{
  mrb_float x, y, z;
  int argc = mrb_get_args(mrb, "fff", &x, &y, &z);

  gp_Vec* vec = NULL;
  if (argc == 3)
    vec = new gp_Vec((Standard_Real)x, (Standard_Real)y, (Standard_Real)z);
  else
    vec = new gp_Vec(0., 0., 0.);

  DATA_PTR(self) = vec;
  DATA_TYPE(self) = &siren_vec_type;
  return self;
}

void siren_vec_final(mrb_state* mrb, void* p)
{
  gp_Vec* v = static_cast<gp_Vec*>(p);
  delete v;
}

mrb_method(vec_to_s)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  return mrb_str_new_cstr(mrb, "#Vec<>");
}

mrb_method(vec_x)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  Standard_Real val = vec->X();
  return mrb_float_value(mrb, (float)val);
}

mrb_method(vec_y)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  Standard_Real val = vec->Y();
  return mrb_float_value(mrb, (float)val);
}

mrb_method(vec_z)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  Standard_Real val = vec->Z();
  return mrb_float_value(mrb, (float)val);
}

mrb_method(vec_to_a)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  mrb_value res[3];
  res[0] = mrb_float_value(mrb, (float)vec->X());
  res[1] = mrb_float_value(mrb, (float)vec->Y());
  res[2] = mrb_float_value(mrb, (float)vec->Z());
  return mrb_ary_new_from_values(mrb, 3, res);
}

mrb_method(vec_to_xyz)
{
  return mrb_method_name(vec_to_a)(mrb, self);
}

gp_Vec* siren_vec_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<gp_Vec*>(mrb_get_datatype(mrb, obj, &siren_vec_type));
}
