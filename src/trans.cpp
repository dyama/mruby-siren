#include "trans.h"

bool siren_trans_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Trans", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", siren_trans_init, ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_translation"   , siren_trans_set_translation,    ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_rotation"      , siren_trans_set_rotation,       ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_scale"         , siren_trans_set_scale,          ARGS_NONE());
  mrb_define_method(mrb, rclass, "scalef"            , siren_trans_scalef,             ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_scalef"        , siren_trans_set_scalef,         ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_mirror"        , siren_trans_set_mirror,         ARGS_NONE());
  mrb_define_method(mrb, rclass, "multiply"          , siren_trans_multiply,           ARGS_NONE());
  mrb_define_method(mrb, rclass, "multiplied"        , siren_trans_multiplied,         ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_transfomation1", siren_trans_set_transfomation1, ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_transfomation2", siren_trans_set_transfomation2, ARGS_NONE());
  return true;
}

mrb_value siren_trans_init(mrb_state* mrb, mrb_value self)
{
  gp_Trsf* trans = new gp_Trsf();
  DATA_PTR(self) = trans;
  DATA_TYPE(self) = &siren_trans_type;
  return self;
}

void siren_trans_final(mrb_state* mrb, void* p)
{
  gp_Trsf* t = static_cast<gp_Trsf*>(p);
  delete t;
}

mrb_value siren_trans_set_translation(mrb_state* mrb, mrb_value self)
{
  mrb_value v;
  int argc = mrb_get_args(mrb, "o", &v);
  gp_Vec*  vec   = siren_vec_get(mrb, v); 
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetTranslation(*vec);
  return mrb_nil_value();
}

mrb_value siren_trans_set_rotation(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  mrb_float angle;
  int argc = mrb_get_args(mrb, "oof", &op, &norm, &angle);
  gp_Vec*  vec_op   = siren_vec_get(mrb, op);
  gp_Vec*  vec_norm = siren_vec_get(mrb, norm);
  gp_Trsf* trans    = siren_trans_get(mrb, self);
  vec_norm->Normalize();
  trans->SetRotation(gp_Ax1(vec2pnt(vec_op), vec2dir(vec_norm)), (Standard_Real)angle);
  return mrb_nil_value();
}

mrb_value siren_trans_set_scale(mrb_state* mrb, mrb_value self)
{
  mrb_value op;
  mrb_float factor;
  int argc = mrb_get_args(mrb, "of", &op, &factor);
  gp_Vec*  vec_op = siren_vec_get(mrb, op);
  gp_Trsf* trans  = siren_trans_get(mrb, self);
  trans->SetScale(vec2pnt(vec_op), (Standard_Real)factor);
  return mrb_nil_value();
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
  trans->SetScaleFactor((Standard_Real)f);
  return mrb_nil_value();
}

mrb_value siren_trans_set_mirror(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  int argc = mrb_get_args(mrb, "oo", &op, &norm);
  gp_Vec*  vec_op   = siren_vec_get(mrb, op);
  gp_Vec*  vec_norm = siren_vec_get(mrb, norm);
  gp_Trsf* trans    = siren_trans_get(mrb, self);
  trans->SetMirror(gp_Ax2(vec2pnt(vec_op), vec2dir(vec_norm)));
  return mrb_nil_value();
}

mrb_value siren_trans_multiply(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  gp_Trsf* trans_me = siren_trans_get(mrb, self);
  gp_Trsf* trans_other = siren_trans_get(mrb, other);
  trans_me->Multiply(*trans_other);
  return mrb_nil_value();
}

mrb_value siren_trans_multiplied(mrb_state* mrb, mrb_value self)
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

mrb_value siren_trans_set_transfomation1(mrb_state* mrb, mrb_value self)
{
  mrb_value op, zv, xv;
  int argc = mrb_get_args(mrb, "ooo", &op, &zv, &xv);
  gp_Pnt p = vec2pnt(siren_vec_get(mrb, op));
  gp_Dir z = vec2dir(siren_vec_get(mrb, zv));
  gp_Dir x = vec2dir(siren_vec_get(mrb, xv));
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetTransformation(gp_Ax3(p, z, x));
  return mrb_nil_value();
}

mrb_value siren_trans_set_transfomation2(mrb_state* mrb, mrb_value self)
{
  mrb_value op1, zv1, xv1;
  mrb_value op2, zv2, xv2;
  int argc = mrb_get_args(mrb, "oooooo", &op1, &zv1, &xv1, &op2, &zv2, &xv2);
  gp_Pnt p1 = vec2pnt(siren_vec_get(mrb, op1));
  gp_Dir z1 = vec2dir(siren_vec_get(mrb, zv1));
  gp_Dir x1 = vec2dir(siren_vec_get(mrb, xv1));
  gp_Pnt p2 = vec2pnt(siren_vec_get(mrb, op2));
  gp_Dir z2 = vec2dir(siren_vec_get(mrb, zv2));
  gp_Dir x2 = vec2dir(siren_vec_get(mrb, xv2));
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetTransformation(gp_Ax3(p1, z1, x1), gp_Ax3(p2, z2, x2));
  return mrb_nil_value();
}

gp_Trsf* siren_trans_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<gp_Trsf*>(mrb_get_datatype(mrb, obj, &siren_trans_type));
}
