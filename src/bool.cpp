#include "bool.h"

bool siren_bool_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Bool");
  return true;
}

