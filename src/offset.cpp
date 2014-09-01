#include "offset.h"

bool siren_offset_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Offset");
  // mrb_define_class_method(mrb, rclass, "sweep_vec", siren_offset_sweep_vec, ARGS_REQ(2));
  return true;
}

