#ifndef _EXP_H_
#define _EXP_H_

#include "siren.h"

#include <TopAbs_ShapeEnum.hxx>
#include <TopExp_Explorer.hxx>

bool siren_exp_install(mrb_state* mrb, struct RClass* rclass);
void siren_exp_final(mrb_state* mrb, void* p);
static struct mrb_data_type siren_exp_type = { "Exp", siren_exp_final };
TopExp_Explorer* siren_exp_get(mrb_state* mrb, mrb_value obj);

mrb_value siren_exp_init(mrb_state* mrb, mrb_value self);
mrb_value siren_exp_to_a(mrb_state* mrb, mrb_value self);

mrb_value siren_exp_init2(mrb_state* mrb, mrb_value self);
mrb_value siren_exp_reinit(mrb_state* mrb, mrb_value self);
mrb_value siren_exp_depth(mrb_state* mrb, mrb_value self);
mrb_value siren_exp_clear(mrb_state* mrb, mrb_value self);
mrb_value siren_exp_more(mrb_state* mrb, mrb_value self);
mrb_value siren_exp_next(mrb_state* mrb, mrb_value self);
mrb_value siren_exp_current(mrb_state* mrb, mrb_value self);

#endif
