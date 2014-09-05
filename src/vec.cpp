#include "vec.h"

mrb_value siren_vec_new(mrb_state* mrb, double x, double y, double z)
{
  mrb_value args[3];
  args[0] = mrb_float_value(mrb, x);
  args[1] = mrb_float_value(mrb, y);
  args[2] = mrb_float_value(mrb, z);
  return mrb_class_new_instance(mrb, 3, args, mrb_class_get(mrb, "Vec"));
}

bool siren_vec_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Vec", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", siren_vec_init,   ARGS_NONE() | ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "to_s",       siren_vec_to_s,   ARGS_NONE());
  mrb_define_method(mrb, rclass, "x",          siren_vec_x,      ARGS_NONE());
  mrb_define_method(mrb, rclass, "y",          siren_vec_y,      ARGS_NONE());
  mrb_define_method(mrb, rclass, "z",          siren_vec_z,      ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_a",       siren_vec_to_a,   ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_xyz",     siren_vec_to_xyz, ARGS_NONE());
  return true;
}

mrb_value siren_vec_init(mrb_state* mrb, mrb_value self)
{
  mrb_float x, y, z;
  int argc = mrb_get_args(mrb, "fff", &x, &y, &z);

  void* p = mrb_malloc(mrb, sizeof(gp_Vec));
  gp_Vec* vec;
  if (argc == 3) {
    vec = new(p) gp_Vec((Standard_Real)x, (Standard_Real)y, (Standard_Real)z);
  }
  else {
    vec = new(p) gp_Vec(0., 0., 0.);
  }

  DATA_PTR(self) = vec;
  DATA_TYPE(self) = &siren_vec_type;
  return self;
}

void siren_vec_final(mrb_state* mrb, void* p)
{
  gp_Vec* v = static_cast<gp_Vec*>(p);
  mrb_free(mrb, v);
}

mrb_value siren_vec_to_s(mrb_state* mrb, mrb_value self)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  return mrb_str_new_cstr(mrb, "#Vec<>");
}

mrb_value siren_vec_x(mrb_state* mrb, mrb_value self)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  Standard_Real val = vec->X();
  return mrb_float_value(mrb, (float)val);
}

mrb_value siren_vec_y(mrb_state* mrb, mrb_value self)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  Standard_Real val = vec->Y();
  return mrb_float_value(mrb, (float)val);
}

mrb_value siren_vec_z(mrb_state* mrb, mrb_value self)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  Standard_Real val = vec->Z();
  return mrb_float_value(mrb, (float)val);
}

mrb_value siren_vec_to_a(mrb_state* mrb, mrb_value self)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  mrb_value res[3];
  res[0] = mrb_float_value(mrb, (float)vec->X());
  res[1] = mrb_float_value(mrb, (float)vec->Y());
  res[2] = mrb_float_value(mrb, (float)vec->Z());
  return mrb_ary_new_from_values(mrb, 3, res);
}

mrb_value siren_vec_to_xyz(mrb_state* mrb, mrb_value self)
{
  return siren_vec_to_a(mrb, self);
}

gp_Vec* siren_vec_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<gp_Vec*>(mrb_get_datatype(mrb, obj, &siren_vec_type));
}
