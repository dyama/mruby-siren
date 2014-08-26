#ifndef _TRANS_H_
#define _TRANS_H_

#include "common.h"
#include "siren.h"
#include "vec.h"

#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax3.hxx>
#include <gp_Trsf.hxx>

bool mrb_siren_trans_install(mrb_state* mrb, struct RClass* rclass);
void mrb_siren_trans_final(mrb_state* mrb, void* p);
static struct mrb_data_type mrb_siren_trans_type = { "Trans", mrb_siren_trans_final };
gp_Trsf* mrb_siren_get_trans(mrb_state* mrb, mrb_value obj);

mrb_method(trans_init);

mrb_method(trans_set_translation);
mrb_method(trans_set_rotation);
mrb_method(trans_set_scale);
mrb_method(trans_scalef);
mrb_method(trans_set_scalef);
mrb_method(trans_set_mirror);
mrb_method(trans_multiply);
mrb_method(trans_multiplied);
mrb_method(trans_set_transfomation1);
mrb_method(trans_set_transfomation2);

#endif
