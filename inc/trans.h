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
mrb_value siren_trans_new(mrb_state* mrb, const gp_Trsf& src);

mrb_value siren_trans_init(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_to_s(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_to_a(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_multiply(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_multiply_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_scalef(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_mirror_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_rotation_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_scale_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_scalef_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_transfomation1_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_transfomation2_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_translation_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_trans_move_point(mrb_state* mrb, mrb_value self);

//mrb_value siren_trans_matrix(mrb_state* mrb, mrb_value self);
//mrb_value siren_trans_set_matrix(mrb_state* mrb, mrb_value self);

#endif
