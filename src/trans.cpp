#include "trans.h"

mrb_data_type* mrb_siren_get_trans_type(void)
{
  return &mrb_siren_trans_type;
}

bool mrb_siren_trans_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Trans", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", mrb_method_name(trans_init), ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_translation"   , mrb_method_name(trans_set_translation),    ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_rotation"      , mrb_method_name(trans_set_rotation),       ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_scale"         , mrb_method_name(trans_set_scale),          ARGS_NONE());
  mrb_define_method(mrb, rclass, "scalef"            , mrb_method_name(trans_scalef),             ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_scalef"        , mrb_method_name(trans_set_scalef),         ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_mirror"        , mrb_method_name(trans_set_mirror),         ARGS_NONE());
  mrb_define_method(mrb, rclass, "multiply"          , mrb_method_name(trans_multiply),           ARGS_NONE());
  mrb_define_method(mrb, rclass, "multiplied"        , mrb_method_name(trans_multiplied),         ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_transfomation1", mrb_method_name(trans_set_transfomation1), ARGS_NONE());
  mrb_define_method(mrb, rclass, "set_transfomation2", mrb_method_name(trans_set_transfomation2), ARGS_NONE());
  return true;
}

mrb_method(trans_init)
{
  gp_Trsf* trans = new gp_Trsf();
  DATA_PTR(self) = trans;
  DATA_TYPE(self) = mrb_siren_get_trans_type();
  return self;
}

void mrb_siren_trans_final(mrb_state* mrb, void* p)
{
  gp_Trsf* t = static_cast<gp_Trsf*>(p);
  delete t;
}

mrb_method(trans_set_translation)
{
  mrb_value v;
  int argc = mrb_get_args(mrb, "o", &v);
  gp_Vec*  vec   = mrb_siren_get_vec(mrb, v); 
  gp_Trsf* trans = mrb_siren_get_trans(mrb, self);
  trans->SetTranslation(*vec);
  return mrb_nil_value();
}

mrb_method(trans_set_rotation)
{
  mrb_value op, norm;
  mrb_float angle;
  int argc = mrb_get_args(mrb, "oof", &op, &norm, &angle);

  gp_Vec*  vec_op   = mrb_siren_get_vec(mrb, op);
  gp_Vec*  vec_norm = mrb_siren_get_vec(mrb, norm);
  gp_Trsf* trans    = mrb_siren_get_trans(mrb, self);

  vec_norm->Normalize();
  trans->SetRotation(gp_Ax1(vec2pnt(vec_op), vec2dir(vec_norm)), (Standard_Real)angle);

  return mrb_nil_value();
}

mrb_method(trans_set_scale)
{
  return mrb_nil_value();
}

mrb_method(trans_scalef)
{
  return mrb_nil_value();
}

mrb_method(trans_set_scalef)
{
  return mrb_nil_value();
}

mrb_method(trans_set_mirror)
{
  return mrb_nil_value();
}

mrb_method(trans_multiply)
{
  return mrb_nil_value();
}

mrb_method(trans_multiplied)
{
  return mrb_nil_value();
}

mrb_method(trans_set_transfomation1)
{
  return mrb_nil_value();
}

mrb_method(trans_set_transfomation2)
{
  return mrb_nil_value();
}

gp_Trsf* mrb_siren_get_trans(mrb_state* mrb, mrb_value obj)
{
  return static_cast<gp_Trsf*>(mrb_get_datatype(mrb, obj, mrb_siren_get_trans_type()));
}
