#ifndef _TRANS_H_
#define _TRANS_H_

#include "siren.h"

#include <gp_Trsf.hxx>

bool mrb_siren_trans_install(mrb_state* mrb, struct RClass* rclass);
void mrb_siren_trans_final(mrb_state* mrb, void* p);

mrb_method(trans_init);

static struct mrb_data_type mrb_siren_trans_type = { "Trans", mrb_siren_trans_final };
mrb_data_type* mrb_siren_get_trans_type(void);

#endif
