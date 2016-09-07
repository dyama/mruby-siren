#include "vec.h"

gp_Vec* siren_vec_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<gp_Vec*>(mrb_get_datatype(mrb, obj, &siren_vec_type));
}

mrb_value siren_vec_new(mrb_state* mrb, double x, double y, double z)
{
  mrb_value arg = mrb_ary_new(mrb);
  mrb_ary_push(mrb, arg, mrb_float_value(mrb, x));
  mrb_ary_push(mrb, arg, mrb_float_value(mrb, y));
  mrb_ary_push(mrb, arg, mrb_float_value(mrb, z));
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  struct RClass* cls_vec = mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Vec")));
  return mrb_class_new_instance(mrb, 1, &arg, cls_vec);
}

mrb_value siren_vec_new(mrb_state* mrb, const gp_Vec& vec)
{
  return siren_vec_new(mrb, vec.X(), vec.Y(), vec.Z());
}

bool siren_vec_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_vec = mrb_define_class_under(mrb, mod_siren, "Vec", mrb->object_class);
  MRB_SET_INSTANCE_TT(cls_vec, MRB_TT_DATA);
  mrb_define_method(mrb, cls_vec, "initialize",       siren_vec_init,             MRB_ARGS_NONE() | MRB_ARGS_OPT(1));
  mrb_define_method(mrb, cls_vec, "inspect",          siren_vec_to_s,             MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "to_s",             siren_vec_to_s,             MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "x",                siren_vec_x,                MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "x=",               siren_vec_x_set,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "y",                siren_vec_y,                MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "y=",               siren_vec_y_set,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "z",                siren_vec_z,                MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "z=",               siren_vec_z_set,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "to_a",             siren_vec_to_a,             MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "to_ary",           siren_vec_to_a,             MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "xyz",              siren_vec_xyz,              MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "equal?",           siren_vec_is_equal,         MRB_ARGS_REQ(3));
  mrb_define_method(mrb, cls_vec, "parallel?",        siren_vec_is_parallel,      MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_vec, "normal?",          siren_vec_is_normal,        MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_vec, "normal",           siren_vec_normal,           MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "normal!",          siren_vec_normal_bang,      MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "reverse?",         siren_vec_is_reverse,       MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_vec, "reverse",          siren_vec_reverse,          MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "reverse!",         siren_vec_reverse_bang,     MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "angle",            siren_vec_angle,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "angleref",         siren_vec_angleref,         MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_vec, "magnitude",        siren_vec_magnitude,        MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "size",             siren_vec_magnitude,        MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "length",           siren_vec_magnitude,        MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_vec, "cross",            siren_vec_cross,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "cross!",           siren_vec_cross_bang,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "dot",              siren_vec_dot,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "dot_cross",        siren_vec_dot_cross,        MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_vec, "cross_cross",      siren_vec_cross_cross,      MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_vec, "cross_cross!",     siren_vec_cross_cross_bang, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_vec, "cross_mag",        siren_vec_cross_mag,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "cross_square_mag", siren_vec_cross_square_mag, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "square_mag",       siren_vec_square_mag,       MRB_ARGS_NONE());

  mrb_define_method(mrb, cls_vec, "mirror",           siren_vec_mirror,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "mirror!",          siren_vec_mirror_bang,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "rotate",           siren_vec_rotate,           MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_vec, "rotate!",          siren_vec_rotate_bang,      MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_vec, "scale",            siren_vec_scale,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "scale!",           siren_vec_scale_bang,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "transform",        siren_vec_transform,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_vec, "transform!",       siren_vec_transform_bang,   MRB_ARGS_REQ(1));

  mrb_define_module_function(mrb, cls_vec, "-@",  siren_vec_negative,         MRB_ARGS_NONE());
  mrb_define_module_function(mrb, cls_vec, "==",  siren_vec_eq,               MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, cls_vec, "+",   siren_vec_plus,             MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, cls_vec, "-",   siren_vec_minus,            MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, cls_vec, "*",   siren_vec_multiply_scalar,  MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, cls_vec, "/",   siren_vec_devide_scalar,    MRB_ARGS_REQ(1));

  return true;
}

mrb_value siren_vec_init(mrb_state* mrb, mrb_value self)
{
  mrb_value ary;
  int argc = mrb_get_args(mrb, "|A", &ary);

  void* p = mrb_malloc(mrb, sizeof(gp_Vec));
  gp_Vec* vec;
  if (argc == 1) {
    gp_Vec v = siren_ary_to_vec(mrb, ary);
    vec = new(p) gp_Vec(v.X(), v.Y(), v.Z());
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
  char str[128];
  snprintf(str, sizeof(str), "#<Vec:0x%x @x=%f, @y=%f, @z=%f>",
      (unsigned int)(uintptr_t)mrb_cptr(self), vec->X(), vec->Y(), vec->Z());
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

mrb_value siren_vec_xyz(mrb_state* mrb, mrb_value self)
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

mrb_value siren_vec_is_reverse(mrb_state* mrb, mrb_value self)
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

mrb_value siren_vec_normal(mrb_state* mrb, mrb_value self)
{
  return siren_vec_new(mrb, siren_vec_get(mrb, self)->Normalized());
}

mrb_value siren_vec_normal_bang(mrb_state* mrb, mrb_value self)
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

mrb_value siren_vec_angleref(mrb_state* mrb, mrb_value self)
{
  mrb_value other, vref;
  int argc = mrb_get_args(mrb, "oo", &other, &vref);
  gp_Vec* me = siren_vec_get(mrb, self);
  gp_Vec* o = siren_vec_get(mrb, other);
  gp_Vec* ref = siren_vec_get(mrb, vref);
  Standard_Real res = me->AngleWithRef(*o, *ref);
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

mrb_value siren_vec_cross(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  gp_Vec ans = siren_vec_get(mrb, self)->Crossed(*siren_vec_get(mrb, other));
  return siren_vec_new(mrb, ans.X(), ans.Y(), ans.Z());
}

mrb_value siren_vec_cross_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  siren_vec_get(mrb, self)->Cross(*siren_vec_get(mrb, other));
  return self;
}

mrb_value siren_vec_dot(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  Standard_Real ans = siren_vec_get(mrb, self)->Dot(*siren_vec_get(mrb, other));
  return mrb_float_value(mrb, ans);
}

mrb_value siren_vec_dot_cross(mrb_state* mrb, mrb_value self)
{
  mrb_value v1, v2;
  int argc = mrb_get_args(mrb, "o", &v1, &v2);
  Standard_Real ans = siren_vec_get(mrb, self)->DotCross(
      *siren_vec_get(mrb, v1),
      *siren_vec_get(mrb, v2));
  return mrb_float_value(mrb, ans);
}

mrb_value siren_vec_cross_cross(mrb_state* mrb, mrb_value self)
{
  mrb_value v1, v2;
  int argc = mrb_get_args(mrb, "o", &v1, &v2);
  gp_Vec ans = siren_vec_get(mrb, self)->CrossCrossed(
      *siren_vec_get(mrb, v1),
      *siren_vec_get(mrb, v2)
      );
  return siren_vec_new(mrb, ans.X(), ans.Y(), ans.Z());
}

mrb_value siren_vec_cross_cross_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value v1, v2;
  int argc = mrb_get_args(mrb, "o", &v1, &v2);
  siren_vec_get(mrb, self)->CrossCross(
      *siren_vec_get(mrb, v1),
      *siren_vec_get(mrb, v2)
      );
  return self;
}

mrb_value siren_vec_cross_mag(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  Standard_Real ans = siren_vec_get(mrb, self)->CrossMagnitude(*siren_vec_get(mrb, other));
  return mrb_float_value(mrb, ans);
}

mrb_value siren_vec_cross_square_mag(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  Standard_Real ans = siren_vec_get(mrb, self)->CrossSquareMagnitude(*siren_vec_get(mrb, other));
  return mrb_float_value(mrb, ans);
}

mrb_value siren_vec_square_mag(mrb_state* mrb, mrb_value self)
{
  Standard_Real res = siren_vec_get(mrb, self)->SquareMagnitude();
  return mrb_float_value(mrb, res);
}

mrb_value siren_vec_mirror(mrb_state* mrb, mrb_value self)
{
  mrb_value dir;
  int argc = mrb_get_args(mrb, "o", &dir);
  gp_Vec res = siren_vec_get(mrb, self)->Mirrored(*siren_vec_get(mrb, dir));
  return siren_vec_new(mrb, res.X(), res.Y(), res.Z());
}

mrb_value siren_vec_mirror_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value dir;
  int argc = mrb_get_args(mrb, "o", &dir);
  siren_vec_get(mrb, self)->Mirror(*siren_vec_get(mrb, dir));
  return self;
}

mrb_value siren_vec_rotate(mrb_state* mrb, mrb_value self)
{
  mrb_value dir;
  mrb_float angle;
  int argc = mrb_get_args(mrb, "of", &dir, &angle);
  gp_Vec res = siren_vec_get(mrb, self)->Rotated(
      gp_Ax1(gp_Pnt(0.0, 0.0, 0.0), *siren_vec_get(mrb, dir)), angle);
  return siren_vec_new(mrb, res.X(), res.Y(), res.Z());
}

mrb_value siren_vec_rotate_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value dir;
  mrb_float angle;
  int argc = mrb_get_args(mrb, "of", &dir, &angle);
  siren_vec_get(mrb, self)->Rotate(
      gp_Ax1(gp_Pnt(0.0, 0.0, 0.0), *siren_vec_get(mrb, dir)), angle);
  return self;
}

mrb_value siren_vec_scale(mrb_state* mrb, mrb_value self)
{
  mrb_float f;
  int argc = mrb_get_args(mrb, "f", &f);
  gp_Vec res = siren_vec_get(mrb, self)->Scaled(f);
  return siren_vec_new(mrb, res.X(), res.Y(), res.Z());
}

mrb_value siren_vec_scale_bang(mrb_state* mrb, mrb_value self)
{
  mrb_float f;
  int argc = mrb_get_args(mrb, "f", &f);
  siren_vec_get(mrb, self)->Scale(f);
  return self;
}

mrb_value siren_vec_transform(mrb_state* mrb, mrb_value self)
{
  mrb_value t;
  int argc = mrb_get_args(mrb, "o", &t);
  gp_Vec res = siren_vec_get(mrb, self)->Transformed(*siren_trans_get(mrb, t));
  return siren_vec_new(mrb, res.X(), res.Y(), res.Z());
}

mrb_value siren_vec_transform_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value t;
  int argc = mrb_get_args(mrb, "o", &t);
  siren_vec_get(mrb, self)->Transform(*siren_trans_get(mrb, t));
  return self;
}

