#ifndef _EXP_H_
#define _EXP_H_

#include "siren.h"

#include <TopAbs_ShapeEnum.hxx>
#include <TopExp_Explorer.hxx>

bool mrb_siren_exp_install(mrb_state* mrb, struct RClass* rclass);
void mrb_siren_exp_final(mrb_state* mrb, void* p);

mrb_method(exp_init);
mrb_method(exp_to_a);

static struct mrb_data_type mrb_siren_exp_type = { "Exp", mrb_siren_exp_final };
mrb_data_type* mrb_siren_get_exp_type(void);

#endif
