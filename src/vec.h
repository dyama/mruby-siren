#ifndef _VEC_H_
#define _VEC_H_

#include "siren.h"

bool mrb_siren_vec_install(mrb_state* mrb, struct RClass* rclass);
void mrb_siren_vec_final(mrb_state* mrb, void* p);

mrb_method(vec_init);
mrb_method(vec_to_s);
mrb_method(vec_x);
mrb_method(vec_y);
mrb_method(vec_z);
mrb_method(vec_to_a);
mrb_method(vec_to_xyz);

static struct mrb_data_type mrb_siren_vec_type = { "Vec", mrb_siren_vec_final };
mrb_data_type* mrb_siren_get_vec_type(void);

gp_Vec* mrb_siren_get_vec(mrb_state* mrb, mrb_value obj);

#endif
