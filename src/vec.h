#ifndef _VEC_H_
#define _VEC_H_

#include "siren.h"

bool siren_vec_install(mrb_state* mrb, struct RClass* rclass);
void siren_vec_final(mrb_state* mrb, void* p);
static struct mrb_data_type siren_vec_type = { "Vec", siren_vec_final };
gp_Vec* siren_vec_get(mrb_state* mrb, mrb_value obj);

mrb_method(vec_init);
mrb_method(vec_to_s);
mrb_method(vec_x);
mrb_method(vec_y);
mrb_method(vec_z);
mrb_method(vec_to_a);
mrb_method(vec_to_xyz);

#endif
