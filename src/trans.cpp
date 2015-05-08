#include "trans.h"

gp_Trsf* siren_trans_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<gp_Trsf*>(mrb_get_datatype(mrb, obj, &siren_trans_type));
}

mrb_value siren_trans_new(mrb_state* mrb, const gp_Trsf& src)
{
  mrb_value res;
  res = mrb_instance_alloc(mrb, mrb_obj_value(mrb_class_get(mrb, "Trans")));
  void* p = mrb_malloc(mrb, sizeof(gp_Trsf));
  gp_Trsf* trans = new(p) gp_Trsf();
  *trans = src;
  DATA_PTR(res) = trans;
  DATA_TYPE(res) = &siren_trans_type;
  return res;
}

bool siren_trans_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Trans", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize"     , siren_trans_init               , ARGS_NONE());
  mrb_define_method(mrb, rclass, "multiply"       , siren_trans_multiply           , ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "multiply!"      , siren_trans_multiply_bang      , ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "scalef"         , siren_trans_scalef             , ARGS_NONE());
  mrb_define_method(mrb, rclass, "mirror!"        , siren_trans_mirror_bang        , ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "rotation!"      , siren_trans_rotation_bang      , ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "scale!"         , siren_trans_scale_bang         , ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "scalef!"        , siren_trans_scalef_bang        , ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "transfomation1!", siren_trans_transfomation1_bang, ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "transfomation2!", siren_trans_transfomation2_bang, ARGS_REQ(6));
  mrb_define_method(mrb, rclass, "translation!"   , siren_trans_translation_bang   , ARGS_REQ(1));
  // mrb_define_method(mrb, rclass, "matrix",        , siren_trans_translation_bang   , ARGS_REQ(1));
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

mrb_value siren_trans_translation_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value v;
  int argc = mrb_get_args(mrb, "A", &v);
  gp_Vec vec = siren_ary_to_vec(mrb, v); 
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetTranslation(vec);
  return mrb_nil_value();
}

mrb_value siren_trans_rotation_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  mrb_float angle;
  int argc = mrb_get_args(mrb, "AAf", &op, &norm, &angle);
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetRotation(siren_ary_to_ax1(mrb, op, norm), angle);
  return mrb_nil_value();
}

mrb_value siren_trans_scale_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op;
  mrb_float factor;
  int argc = mrb_get_args(mrb, "Af", &op, &factor);
  gp_Trsf* trans  = siren_trans_get(mrb, self);
  trans->SetScale(siren_ary_to_pnt(mrb, op), factor);
  return mrb_nil_value();
}

mrb_value siren_trans_scalef(mrb_state* mrb, mrb_value self)
{
  gp_Trsf* trans  = siren_trans_get(mrb, self);
  Standard_Real f = trans->ScaleFactor();
  return mrb_float_value(mrb, f);
}

mrb_value siren_trans_scalef_bang(mrb_state* mrb, mrb_value self)
{
  mrb_float f;
  int argc = mrb_get_args(mrb, "f", &f);
  gp_Trsf* trans  = siren_trans_get(mrb, self);
  trans->SetScaleFactor(f);
  return mrb_nil_value();
}

mrb_value siren_trans_mirror_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  int argc = mrb_get_args(mrb, "AA", &op, &norm);
  gp_Trsf* trans    = siren_trans_get(mrb, self);
  trans->SetMirror(siren_ary_to_ax2(mrb, op, norm));
  return mrb_nil_value();
}

mrb_value siren_trans_multiply_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  gp_Trsf* trans_me = siren_trans_get(mrb, self);
  gp_Trsf* trans_other = siren_trans_get(mrb, other);
  trans_me->Multiply(*trans_other);
  return mrb_nil_value();
}

mrb_value siren_trans_multiply(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  gp_Trsf* trans_me = siren_trans_get(mrb, self);
  gp_Trsf* trans_other = siren_trans_get(mrb, other);
  mrb_value res = mrb_class_new_instance(mrb, 0, NULL, mrb_class_get(mrb, "Trans"));
  gp_Trsf* t = siren_trans_get(mrb, res);
  *t = trans_me->Multiplied(*trans_other);
  return res;
}

mrb_value siren_trans_transfomation1_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op, zv, xv;
  int argc = mrb_get_args(mrb, "AAA", &op, &zv, &xv);
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetTransformation(siren_ary_to_ax3(mrb, op, zv, xv));
  return mrb_nil_value();
}

mrb_value siren_trans_transfomation2_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op1, zv1, xv1;
  mrb_value op2, zv2, xv2;
  int argc = mrb_get_args(mrb, "AAAAAA", &op1, &zv1, &xv1, &op2, &zv2, &xv2);
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetTransformation(siren_ary_to_ax3(mrb, op1, zv1, xv1), siren_ary_to_ax3(mrb, op2, zv2, xv2));
  return mrb_nil_value();
}

mrb_value siren_trans_value(mrb_state* mrb, mrb_value self)
{
  return mrb_nil_value();
}

mrb_value siren_trans_set_value(mrb_state* mrb, mrb_value self)
{
  return mrb_nil_value();
}

