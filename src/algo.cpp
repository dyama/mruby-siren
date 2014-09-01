#include "algo.h"

bool siren_algo_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Algo");
  // mrb_define_class_method(mrb, rclass, "section", siren_algo_section, ARGS_REQ(2));
  return true;
}

