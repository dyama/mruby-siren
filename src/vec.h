#ifndef _VEC_H_
#define _VEC_H_

#include "siren.h"

bool siren_vec_install(mrb_state* mrb, struct RClass* rclass);
void siren_vec_final(mrb_state* mrb, void* p);
static struct mrb_data_type siren_vec_type = { "Vec", siren_vec_final };
gp_Vec* siren_vec_get(mrb_state* mrb, mrb_value obj);
mrb_value siren_vec_new(mrb_state* mrb, double x, double y, double z);

mrb_value siren_vec_init(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_to_s(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_x(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_x_set(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_y(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_y_set(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_z(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_z_set(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_to_a(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_to_xyz(mrb_state* mrb, mrb_value self);

#endif
