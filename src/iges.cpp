#include "iges.h"

bool siren_iges_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "IGES");
  mrb_define_class_method(mrb, rclass, "save", siren_iges_save, ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "load", siren_iges_load, ARGS_REQ(1));
  return true;
}

mrb_value siren_iges_save(mrb_state* mrb, mrb_value self)
{
  return mrb_nil_value();
}

mrb_value siren_iges_load(mrb_state* mrb, mrb_value self)
{
  return mrb_nil_value();
}

