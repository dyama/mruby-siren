#include "vec.h"

gp_Vec* siren_vec_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<gp_Vec*>(mrb_get_datatype(mrb, obj, &siren_vec_type));
}

mrb_value siren_vec_new(mrb_state* mrb, double x, double y, double z)
{
  mrb_value args[3];
  args[0] = mrb_float_value(mrb, x);
  args[1] = mrb_float_value(mrb, y);
  args[2] = mrb_float_value(mrb, z);
  return mrb_class_new_instance(mrb, 3, args, mrb_class_get(mrb, "Vec"));
}

mrb_value siren_vec_new(mrb_state* mrb, const gp_Vec& vec)
{
  return siren_vec_new(mrb, vec.X(), vec.Y(), vec.Z());
}

bool siren_vec_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Vec", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", siren_vec_init,           ARGS_NONE() | ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "inspect",    siren_vec_to_s,           ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_s",       siren_vec_to_s,           ARGS_NONE());
  mrb_define_method(mrb, rclass, "x",          siren_vec_x,              ARGS_NONE());
  mrb_define_method(mrb, rclass, "x=",         siren_vec_x_set,          ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "y",          siren_vec_y,              ARGS_NONE());
  mrb_define_method(mrb, rclass, "y=",         siren_vec_y_set,          ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "z",          siren_vec_z,              ARGS_NONE());
  mrb_define_method(mrb, rclass, "z=",         siren_vec_z_set,          ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "to_a",       siren_vec_to_a,           ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_xyz",     siren_vec_to_xyz,         ARGS_NONE());
  mrb_define_method(mrb, rclass, "equal?",     siren_vec_is_equal,       ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "normal?",    siren_vec_is_normal,      ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "opposite?",  siren_vec_is_opposite,    ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "parallel?",  siren_vec_is_parallel,    ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "normalize",  siren_vec_normalize,      ARGS_NONE());
  mrb_define_method(mrb, rclass, "normalize!", siren_vec_normalize_bang, ARGS_NONE());
  mrb_define_method(mrb, rclass, "reverse",    siren_vec_reverse,        ARGS_NONE());
  mrb_define_method(mrb, rclass, "reverse!",   siren_vec_reverse_bang,   ARGS_NONE());
  mrb_define_method(mrb, rclass, "angle",      siren_vec_angle,          ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "magnitude",  siren_vec_magnitude,      ARGS_NONE());
  mrb_define_method(mrb, rclass, "size",       siren_vec_magnitude,      ARGS_NONE());
  mrb_define_method(mrb, rclass, "length",     siren_vec_magnitude,      ARGS_NONE());
  return true;
}

mrb_value siren_vec_init(mrb_state* mrb, mrb_value self)
{
  mrb_float x, y, z;
  int argc = mrb_get_args(mrb, "|fff", &x, &y, &z);

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
  char str[64];
  snprintf(str, sizeof(str), "#Vec<x=%f, y=%f, z=%f>", vec->X(), vec->Y(), vec->Z());
  return mrb_str_new_cstr(mrb, str);
}

mrb_value siren_vec_x(mrb_state* mrb, mrb_value self)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  return mrb_float_value(mrb, (float)vec->X());
}

mrb_value siren_vec_x_set(mrb_state* mrb, mrb_value self)
{
  mrb_float val;
  int argc = mrb_get_args(mrb, "f", &val);
  gp_Vec* vec = siren_vec_get(mrb, self);
  vec->SetX((Standard_Real)val);
  return mrb_float_value(mrb, (float)vec->X());
}

mrb_value siren_vec_y(mrb_state* mrb, mrb_value self)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  Standard_Real val = vec->Y();
  return mrb_float_value(mrb, (float)val);
}

mrb_value siren_vec_y_set(mrb_state* mrb, mrb_value self)
{
  mrb_float val;
  int argc = mrb_get_args(mrb, "f", &val);
  gp_Vec* vec = siren_vec_get(mrb, self);
  vec->SetY((Standard_Real)val);
  return mrb_float_value(mrb, (float)vec->Y());
}

mrb_value siren_vec_z(mrb_state* mrb, mrb_value self)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  Standard_Real val = vec->Z();
  return mrb_float_value(mrb, (float)val);
}

mrb_value siren_vec_z_set(mrb_state* mrb, mrb_value self)
{
  mrb_float val;
  int argc = mrb_get_args(mrb, "f", &val);
  gp_Vec* vec = siren_vec_get(mrb, self);
  vec->SetZ((Standard_Real)val);
  return mrb_float_value(mrb, (float)vec->Z());
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

mrb_value siren_vec_is_equal(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  mrb_float lintol, angtol;
  int argc = mrb_get_args(mrb, "off", &other, &lintol, &angtol);
  gp_Vec* me = siren_vec_get(mrb, self);
  gp_Vec* o = siren_vec_get(mrb, other);
  Standard_Boolean res = me->IsEqual(*o, (Standard_Real)lintol, (Standard_Real)angtol);
  return res ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_vec_is_normal(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  mrb_float angtol;
  int argc = mrb_get_args(mrb, "of", &other, &angtol);
  gp_Vec* me = siren_vec_get(mrb, self);
  gp_Vec* o = siren_vec_get(mrb, other);
  Standard_Boolean res = me->IsNormal(*o, (Standard_Real)angtol);
  return res ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_vec_is_opposite(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  mrb_float angtol;
  int argc = mrb_get_args(mrb, "of", &other, &angtol);
  gp_Vec* me = siren_vec_get(mrb, self);
  gp_Vec* o = siren_vec_get(mrb, other);
  Standard_Boolean res = me->IsOpposite(*o, (Standard_Real)angtol);
  return res ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_vec_is_parallel(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  mrb_float angtol;
  int argc = mrb_get_args(mrb, "of", &other, &angtol);
  gp_Vec* me = siren_vec_get(mrb, self);
  gp_Vec* o = siren_vec_get(mrb, other);
  Standard_Boolean res = me->IsParallel(*o, (Standard_Real)angtol);
  return res ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_vec_normalize(mrb_state* mrb, mrb_value self)
{
  return siren_vec_new(mrb, siren_vec_get(mrb, self)->Normalized());
}

mrb_value siren_vec_normalize_bang(mrb_state* mrb, mrb_value self)
{
  siren_vec_get(mrb, self)->Normalize();
  return self;
}

mrb_value siren_vec_reverse(mrb_state* mrb, mrb_value self)
{
  return siren_vec_new(mrb, siren_vec_get(mrb, self)->Reversed());
}

mrb_value siren_vec_reverse_bang(mrb_state* mrb, mrb_value self)
{
  siren_vec_get(mrb, self)->Reverse();
  return self;
}

mrb_value siren_vec_angle(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  gp_Vec* me = siren_vec_get(mrb, self);
  gp_Vec* o = siren_vec_get(mrb, other);
  Standard_Real res = me->Angle(*o);
  return mrb_float_value(mrb, (float)res);
}

mrb_value siren_vec_magnitude(mrb_state* mrb, mrb_value self)
{
  Standard_Real res = siren_vec_get(mrb, self)->Magnitude();
  return mrb_float_value(mrb, (float)res);
}

