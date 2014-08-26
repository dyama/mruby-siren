#include "prim.h"

bool siren_prim_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Prim");
  return true;
}

