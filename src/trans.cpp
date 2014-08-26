#include "trans.h"

mrb_data_type* mrb_siren_get_trans_type(void)
{
  return &mrb_siren_trans_type;
}

bool mrb_siren_trans_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Trans", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", mrb_method_name(trans_init),   ARGS_NONE());
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

