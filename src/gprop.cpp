#include "gprop.h"

bool siren_gprop_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "GProp");
  return true;
}

