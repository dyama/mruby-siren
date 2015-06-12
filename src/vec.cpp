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
  mrb_define_method(mrb, rclass, "initialize", siren_vec_init,           MRB_ARGS_NONE() | MRB_ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "inspect",    siren_vec_to_s,           MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_s",       siren_vec_to_s,           MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "x",          siren_vec_x,              MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "x=",         siren_vec_x_set,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "y",          siren_vec_y,              MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "y=",         siren_vec_y_set,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "z",          siren_vec_z,              MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "z=",         siren_vec_z_set,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "to_a",       siren_vec_to_a,           MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_ary",     siren_vec_to_a,           MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_xyz",     siren_vec_to_xyz,         MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "equal?",     siren_vec_is_equal,       MRB_ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "normal?",    siren_vec_is_normal,      MRB_ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "opposite?",  siren_vec_is_opposite,    MRB_ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "parallel?",  siren_vec_is_parallel,    MRB_ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "normalize",  siren_vec_normalize,      MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "normalize!", siren_vec_normalize_bang, MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "reverse",    siren_vec_reverse,        MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "reverse!",   siren_vec_reverse_bang,   MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "angle",      siren_vec_angle,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "magnitude",  siren_vec_magnitude,      MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "size",       siren_vec_magnitude,      MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "length",     siren_vec_magnitude,      MRB_ARGS_NONE());

  mrb_define_module_function(mrb, rclass, "-@", siren_vec_negative,        MRB_ARGS_NONE());
  mrb_define_module_function(mrb, rclass, "==", siren_vec_eq,              MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, rclass, "+",  siren_vec_plus,            MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, rclass, "-",  siren_vec_minus,           MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, rclass, "*",  siren_vec_multiply_scalar, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, rclass, "/",  siren_vec_devide_scalar,   MRB_ARGS_REQ(1));

  mrb_define_module_function(mrb, rclass, "zero", siren_vec_zero,   MRB_ARGS_NONE());
  mrb_define_module_function(mrb, rclass, "origin", siren_vec_zero, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, rclass, "xdir", siren_vec_xdir,   MRB_ARGS_NONE());
  mrb_define_module_function(mrb, rclass, "ydir", siren_vec_ydir,   MRB_ARGS_NONE());
  mrb_define_module_function(mrb, rclass, "zdir", siren_vec_zdir,   MRB_ARGS_NONE());

  return true;
}

mrb_value siren_vec_init(mrb_state* mrb, mrb_value self)
{
  mrb_float x, y, z;
  int argc = mrb_get_args(mrb, "|fff", &x, &y, &z);

  void* p = mrb_malloc(mrb, sizeof(gp_Vec));
  gp_Vec* vec;
  if (argc == 3) {
    vec = new(p) gp_Vec(x, y, z);
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
  return mrb_float_value(mrb, siren_vec_get(mrb, self)->X());
}

mrb_value siren_vec_x_set(mrb_state* mrb, mrb_value self)
{
  mrb_float val;
  int argc = mrb_get_args(mrb, "f", &val);
  gp_Vec* vec = siren_vec_get(mrb, self);
  vec->SetX(val);
  return mrb_float_value(mrb, vec->X());
}

mrb_value siren_vec_y(mrb_state* mrb, mrb_value self)
{
  return mrb_float_value(mrb, siren_vec_get(mrb, self)->Y());
}

mrb_value siren_vec_y_set(mrb_state* mrb, mrb_value self)
{
  mrb_float val;
  int argc = mrb_get_args(mrb, "f", &val);
  gp_Vec* vec = siren_vec_get(mrb, self);
  vec->SetY(val);
  return mrb_float_value(mrb, vec->Y());
}

mrb_value siren_vec_z(mrb_state* mrb, mrb_value self)
{
  return mrb_float_value(mrb, siren_vec_get(mrb, self)->Z());
}

mrb_value siren_vec_z_set(mrb_state* mrb, mrb_value self)
{
  mrb_float val;
  int argc = mrb_get_args(mrb, "f", &val);
  gp_Vec* vec = siren_vec_get(mrb, self);
  vec->SetZ(val);
  return mrb_float_value(mrb, vec->Z());
}

mrb_value siren_vec_to_a(mrb_state* mrb, mrb_value self)
{
  gp_Vec* vec = siren_vec_get(mrb, self);
  return siren_vec_to_ary(mrb, *vec);
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
  Standard_Boolean res = me->IsEqual(*o, lintol, angtol);
  return res ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_vec_is_normal(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  mrb_float angtol;
  int argc = mrb_get_args(mrb, "of", &other, &angtol);
  gp_Vec* me = siren_vec_get(mrb, self);
  gp_Vec* o = siren_vec_get(mrb, other);
  Standard_Boolean res = me->IsNormal(*o, angtol);
  return res ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_vec_is_opposite(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  mrb_float angtol;
  int argc = mrb_get_args(mrb, "of", &other, &angtol);
  gp_Vec* me = siren_vec_get(mrb, self);
  gp_Vec* o = siren_vec_get(mrb, other);
  Standard_Boolean res = me->IsOpposite(*o, angtol);
  return res ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_vec_is_parallel(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  mrb_float angtol;
  int argc = mrb_get_args(mrb, "of", &other, &angtol);
  gp_Vec* me = siren_vec_get(mrb, self);
  gp_Vec* o = siren_vec_get(mrb, other);
  Standard_Boolean res = me->IsParallel(*o, angtol);
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
  return mrb_float_value(mrb, res);
}

mrb_value siren_vec_magnitude(mrb_state* mrb, mrb_value self)
{
  Standard_Real res = siren_vec_get(mrb, self)->Magnitude();
  return mrb_float_value(mrb, res);
}

mrb_value siren_vec_negative(mrb_state* mrb, mrb_value self)
{
  gp_Vec ans = -(*siren_vec_get(mrb, self));
  return siren_vec_new(mrb, ans.X(), ans.Y(), ans.Z());
}

mrb_value siren_vec_eq(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  Standard_Real lintol = 0.0, angtol = 0.0; // to be use the default tolerance value
  Standard_Boolean ans = siren_vec_get(mrb, self)->IsEqual(*siren_vec_get(mrb, other), lintol, angtol);
  return ans ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_vec_plus(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  gp_Vec ans = *siren_vec_get(mrb, self) + *siren_vec_get(mrb, other);
  return siren_vec_new(mrb, ans.X(), ans.Y(), ans.Z());
}

mrb_value siren_vec_minus(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  gp_Vec ans = *siren_vec_get(mrb, self) - *siren_vec_get(mrb, other);
  return siren_vec_new(mrb, ans.X(), ans.Y(), ans.Z());
}

mrb_value siren_vec_multiply_scalar(mrb_state* mrb, mrb_value self)
{
  mrb_float factor;
  int argc = mrb_get_args(mrb, "f", &factor);
  gp_Vec ans = *siren_vec_get(mrb, self) * factor;
  return siren_vec_new(mrb, ans.X(), ans.Y(), ans.Z());
}

mrb_value siren_vec_devide_scalar(mrb_state* mrb, mrb_value self)
{
  mrb_float factor;
  int argc = mrb_get_args(mrb, "f", &factor);
  gp_Vec ans = *siren_vec_get(mrb, self) / factor;
  return siren_vec_new(mrb, ans.X(), ans.Y(), ans.Z());
}

mrb_value siren_vec_zero(mrb_state* mrb, mrb_value self)
{
  return siren_vec_new(mrb, 0.0, 0.0, 0.0);
}

mrb_value siren_vec_xdir(mrb_state* mrb, mrb_value self)
{
  return siren_vec_new(mrb, 1.0, 0.0, 0.0);
}

mrb_value siren_vec_ydir(mrb_state* mrb, mrb_value self)
{
  return siren_vec_new(mrb, 0.0, 1.0, 0.0);
}

mrb_value siren_vec_zdir(mrb_state* mrb, mrb_value self)
{
  return siren_vec_new(mrb, 0.0, 0.0, 1.0);
}

mrb_value siren_vec_xdir_neg(mrb_state* mrb, mrb_value self)
{
  return siren_vec_new(mrb, -1.0, 0.0, 0.0);
}

mrb_value siren_vec_ydir_neg(mrb_state* mrb, mrb_value self)
{
  return siren_vec_new(mrb, 0.0, -1.0, 0.0);
}

mrb_value siren_vec_zdir_neg(mrb_state* mrb, mrb_value self)
{
  return siren_vec_new(mrb, 0.0, 0.0, -1.0);
}

