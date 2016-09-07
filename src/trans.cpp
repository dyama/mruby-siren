#include "trans.h"

gp_Trsf* siren_trans_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<gp_Trsf*>(mrb_get_datatype(mrb, obj, &siren_trans_type));
}

mrb_value siren_trans_new(mrb_state* mrb, const gp_Trsf& src)
{
  mrb_value res;
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  struct RClass* cls_trans = mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Trans")));
  res = mrb_instance_alloc(mrb, mrb_obj_value(cls_trans));
  void* p = mrb_malloc(mrb, sizeof(gp_Trsf));
  gp_Trsf* trans = new(p) gp_Trsf();
  *trans = src;
  DATA_PTR(res) = trans;
  DATA_TYPE(res) = &siren_trans_type;
  return res;
}

bool siren_trans_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* rclass = mrb_define_class_under(mrb, mod_siren, "Trans", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize"     , siren_trans_init               , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "inspect"        , siren_trans_to_s               , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_s"           , siren_trans_to_s               , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_a"           , siren_trans_matrix             , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_ary"         , siren_trans_matrix             , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "matrix"         , siren_trans_matrix             , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "matrix="        , siren_trans_set_matrix         , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "multiply"       , siren_trans_multiply           , MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "multiply!"      , siren_trans_multiply_bang      , MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "power"          , siren_trans_power              , MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "power!"         , siren_trans_power_bang         , MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "translate!"     , siren_trans_translate_bang     , MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "translatef"     , siren_trans_translatef         , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "translatef="    , siren_trans_set_translatef     , MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "mirror!"        , siren_trans_mirror_bang        , MRB_ARGS_REQ(1) | MRB_ARGS_OPT(2));
  mrb_define_method(mrb, rclass, "rotate!"        , siren_trans_rotate_bang        , MRB_ARGS_REQ(3));
//  mrb_define_method(mrb, rclass, "rotatef"        , siren_trans_rotatef            , MRB_ARGS_NONE());
//  mrb_define_method(mrb, rclass, "rotatef="       , siren_trans_set_rotatef        , MRB_ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "scale!"         , siren_trans_scale_bang         , MRB_ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "scalef"         , siren_trans_scalef             , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "scalef="        , siren_trans_set_scalef         , MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "invert"         , siren_trans_invert             , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "invert!"        , siren_trans_invert_bang        , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "reverse"        , siren_trans_invert             , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "reverse!"       , siren_trans_invert_bang        , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "negative?"      , siren_trans_is_negative        , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "transform!"     , siren_trans_transform_bang     , MRB_ARGS_REQ(6));

  mrb_define_method(mrb, rclass, "move_point"     , siren_trans_move_point         , MRB_ARGS_REQ(1));
  return true;
}

mrb_value siren_trans_init(mrb_state* mrb, mrb_value self)
{
  void* p = mrb_malloc(mrb, sizeof(gp_Trsf));
  gp_Trsf* trans = new(p) gp_Trsf();
  DATA_PTR(self) = trans;
  DATA_TYPE(self) = &siren_trans_type;
  return self;
}

void siren_trans_final(mrb_state* mrb, void* p)
{
  gp_Trsf* t = static_cast<gp_Trsf*>(p);
  mrb_free(mrb, t);
}

mrb_value siren_trans_to_s(mrb_state* mrb, mrb_value self)
{
  char str[256];
  Standard_Real a11 = siren_trans_get(mrb, self)->Value(1, 1);
  Standard_Real a12 = siren_trans_get(mrb, self)->Value(1, 2);
  Standard_Real a13 = siren_trans_get(mrb, self)->Value(1, 3);
  Standard_Real a14 = siren_trans_get(mrb, self)->Value(1, 4);
  Standard_Real a21 = siren_trans_get(mrb, self)->Value(2, 1);
  Standard_Real a22 = siren_trans_get(mrb, self)->Value(2, 2);
  Standard_Real a23 = siren_trans_get(mrb, self)->Value(2, 3);
  Standard_Real a24 = siren_trans_get(mrb, self)->Value(2, 4);
  Standard_Real a31 = siren_trans_get(mrb, self)->Value(3, 1);
  Standard_Real a32 = siren_trans_get(mrb, self)->Value(3, 2);
  Standard_Real a33 = siren_trans_get(mrb, self)->Value(3, 3);
  Standard_Real a34 = siren_trans_get(mrb, self)->Value(3, 4);
  snprintf(str, sizeof(str),
      "#<Trans:0x%x\n"
      "    X = % 2.6f, % 2.6f, % 2.6f\n"
      "    Y = % 2.6f, % 2.6f, % 2.6f\n"
      "    Z = % 2.6f, % 2.6f, % 2.6f\n"
      "    T = % 2.6f, % 2.6f, % 2.6f>",
      (unsigned int)(uintptr_t)mrb_cptr(self),
      a11, a21, a31,
      a12, a22, a32,
      a13, a23, a33,
      a14, a24, a34
      );
  return mrb_str_new_cstr(mrb, str);
}

mrb_value siren_trans_translate_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value v;
  int argc = mrb_get_args(mrb, "A", &v);
  gp_Vec vec = siren_ary_to_vec(mrb, v); 
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetTranslation(vec);
  return self;
}

mrb_value siren_trans_rotate_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  mrb_float angle;
  int argc = mrb_get_args(mrb, "AAf", &op, &norm, &angle);
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetRotation(siren_ary_to_ax1(mrb, op, norm), angle);
  return self;
}

/*
mrb_value siren_trans_rotatef(mrb_state* mrb, mrb_value self)
{
  gp_XYZ axis;
  Standard_Real angle;
  if (siren_trans_get(mrb, self)->GetRotation(axis, angle) == Standard_False) {
    return mrb_nil_value();
  }
  mrb_value res[] = {
    siren_pnt_new(mrb, axis.X(), axis.Y(), axis.Z()),
    mrb_float_value(mrb, angle)
  };
  return mrb_ary_new_from_values(mrb, 2, res);
}

mrb_value siren_trans_set_rotatef(mrb_state* mrb, mrb_value self)
{
  return mrb_nil_value();
}
*/

mrb_value siren_trans_scale_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op;
  mrb_float factor;
  int argc = mrb_get_args(mrb, "Af", &op, &factor);
  gp_Trsf* trans  = siren_trans_get(mrb, self);
  trans->SetScale(siren_ary_to_pnt(mrb, op), factor);
  return self;
}

mrb_value siren_trans_scalef(mrb_state* mrb, mrb_value self)
{
  gp_Trsf* trans  = siren_trans_get(mrb, self);
  Standard_Real f = trans->ScaleFactor();
  return mrb_float_value(mrb, f);
}

mrb_value siren_trans_set_scalef(mrb_state* mrb, mrb_value self)
{
  mrb_float f;
  int argc = mrb_get_args(mrb, "f", &f);
  gp_Trsf* trans  = siren_trans_get(mrb, self);
  trans->SetScaleFactor(f);
  return mrb_float_value(mrb, f);
}

mrb_value siren_trans_mirror_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm, vx;
  int argc = mrb_get_args(mrb, "A|AA", &op, &norm, &vx);
  switch (argc) {
  case 1:
    siren_trans_get(mrb, self)->SetMirror(siren_ary_to_pnt(mrb, op));
    break;
  case 2:
    siren_trans_get(mrb, self)->SetMirror(siren_ary_to_ax1(mrb, op, norm));
    break;
  case 3:
    siren_trans_get(mrb, self)->SetMirror(siren_ary_to_ax2(mrb, op, norm, vx));
    break;
  }
  return self;
}

mrb_value siren_trans_multiply(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  gp_Trsf* trans_me = siren_trans_get(mrb, self);
  gp_Trsf* trans_other = siren_trans_get(mrb, other);
  gp_Trsf t = trans_me->Multiplied(*trans_other);
  return siren_trans_new(mrb, t);
}

mrb_value siren_trans_multiply_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  gp_Trsf* trans_me = siren_trans_get(mrb, self);
  gp_Trsf* trans_other = siren_trans_get(mrb, other);
  trans_me->Multiply(*trans_other);
  return self;
}

mrb_value siren_trans_power(mrb_state* mrb, mrb_value self)
{
  mrb_int n;
  int argc = mrb_get_args(mrb, "i", &n);
  return siren_trans_new(mrb, siren_trans_get(mrb, self)->Powered(n));
}

mrb_value siren_trans_power_bang(mrb_state* mrb, mrb_value self)
{
  mrb_int n;
  int argc = mrb_get_args(mrb, "i", &n);
  siren_trans_get(mrb, self)->Power(n);
  return self;
}

mrb_value siren_trans_invert(mrb_state* mrb, mrb_value self)
{
  return siren_trans_new(mrb, siren_trans_get(mrb, self)->Inverted());
}

mrb_value siren_trans_invert_bang(mrb_state* mrb, mrb_value self)
{
  siren_trans_get(mrb, self)->Invert();
  return self;
}

mrb_value siren_trans_is_negative(mrb_state* mrb, mrb_value self)
{
  return siren_trans_get(mrb, self)->IsNegative() ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_trans_transform_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value pos1, norm1, vdir1;
  mrb_value pos2, norm2, vdir2;
  int argc = mrb_get_args(mrb, "AAA|AAA", &pos1, &norm1, &vdir1, &pos2, &norm2, &vdir2);
  gp_Trsf* trans = siren_trans_get(mrb, self);
  if (argc == 3) {
    trans->SetTransformation(siren_ary_to_ax3(mrb, pos1, norm1, vdir1));
  }
  else if (argc == 6) {
    trans->SetTransformation(siren_ary_to_ax3(mrb, pos1, norm1, vdir1), siren_ary_to_ax3(mrb, pos2, norm2, vdir2));
  }
  else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Number of arguments is wrong.");
  }
  return self;
}

mrb_value siren_trans_matrix(mrb_state* mrb, mrb_value self)
{
  mrb_value result[4];
  for (int row = 1; row <= 4; row++) {
    result[row - 1] = mrb_ary_new(mrb);
    for (int col = 1; col <= 3; col++) {
      mrb_ary_push(mrb, result[row - 1], 
          mrb_float_value(mrb, siren_trans_get(mrb, self)->Value(col, row)));
    }
  }
  return mrb_ary_new_from_values(mrb, 4, result);
}

mrb_value siren_trans_set_matrix(mrb_state* mrb, mrb_value self)
{
  mrb_value ary;
  int argc = mrb_get_args(mrb, "A", &ary);
  if (mrb_ary_len(mrb, ary) != 4) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Number of items of specified array is wrong.");
  }
  gp_Vec x = siren_ary_to_vec(mrb, mrb_ary_ref(mrb, ary, 0));
  gp_Vec y = siren_ary_to_vec(mrb, mrb_ary_ref(mrb, ary, 1));
  gp_Vec z = siren_ary_to_vec(mrb, mrb_ary_ref(mrb, ary, 2));
  gp_Vec t = siren_ary_to_vec(mrb, mrb_ary_ref(mrb, ary, 3));
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetValues(
      x.X(), y.X(), z.X(), t.X(), 
      x.Y(), y.Y(), z.Y(), t.Y(), 
      x.Z(), y.Z(), z.Z(), t.Z());
  return self;
}

mrb_value siren_trans_translatef(mrb_state* mrb, mrb_value self)
{
  gp_Trsf* trans = siren_trans_get(mrb, self);
  gp_XYZ xyz = trans->TranslationPart();
  return siren_pnt_new(mrb, xyz.X(), xyz.Y(), xyz.Z());
}

mrb_value siren_trans_set_translatef(mrb_state* mrb, mrb_value self)
{
  mrb_value v;
  int argc = mrb_get_args(mrb, "o", &v);
  siren_trans_get(mrb, self)->SetTranslationPart(siren_ary_to_vec(mrb, v));
  return mrb_nil_value();
}

mrb_value siren_trans_move_point(mrb_state* mrb, mrb_value self)
{
  mrb_value ary;
  int argc = mrb_get_args(mrb, "A", &ary);
  gp_Pnt point = siren_ary_to_pnt(mrb, ary);
  gp_Trsf* trans = siren_trans_get(mrb, self);
  point.Transform(*trans);
  return siren_pnt_to_ary(mrb, point);
}

