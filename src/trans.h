#ifndef _TRANS_H_
#define _TRANS_H_

#include "common.h"
#include "siren.h"
#include "vec.h"

#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax3.hxx>
#include <gp_Trsf.hxx>

bool siren_trans_install(mrb_state* mrb, struct RClass* rclass);
void siren_trans_final(mrb_state* mrb, void* p);
static struct mrb_data_type siren_trans_type = { "Trans", siren_trans_final };
gp_Trsf* siren_trans_get(mrb_state* mrb, mrb_value obj);

mrb_value siren_trans_init(mrb_state* mrb, mrb_value self);

mrb_value siren_trans_set_translation(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_set_rotation(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_set_scale(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_scalef(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_set_scalef(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_set_mirror(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_multiply(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_multiplied(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_set_transfomation1(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_set_transfomation2(mrb_state* mrb, mrb_value self);

#endif
