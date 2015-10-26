#ifndef _VEC_H_
#define _VEC_H_

#include "siren.h"

bool siren_vec_install(mrb_state* mrb, struct RClass* rclass);
void siren_vec_final(mrb_state* mrb, void* p);
static struct mrb_data_type siren_vec_type = { "Vec", siren_vec_final };
gp_Vec* siren_vec_get(mrb_state* mrb, mrb_value obj);
mrb_value siren_vec_new(mrb_state* mrb, double x, double y, double z);
mrb_value siren_vec_new(mrb_state* mrb, const gp_Vec& vec);

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

mrb_value siren_vec_is_equal(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_is_normal(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_is_reverse(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_is_parallel(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_angle(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_angleref(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_magnitude(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_square_magnitude(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_add(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_add_bang(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_subtract(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_subtract_bang(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_multiply(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_multiply_bang(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_divide(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_divide_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_cross(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_cross_bang(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_cross_magnitude(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_cross_cross(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_cross_cross_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_dot(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_dot_cross(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_normal(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_normal_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_reverse(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_reverse_bang(mrb_state* mrb, mrb_value self);
// 
// mrb_value siren_vec_coord(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_coord_set(mrb_state* mrb, mrb_value self);
// 
// mrb_value siren_vec_mirror(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_mirror_bang(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_rotate(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_rotate_bang(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_scale(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_scale_bang(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_transform(mrb_state* mrb, mrb_value self);
// mrb_value siren_vec_transform_bang(mrb_state* mrb, mrb_value self);

mrb_value siren_vec_negative(mrb_state* mrb, mrb_value self);

mrb_value siren_vec_eq(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_plus(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_minus(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_multiply_scalar(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_devide_scalar(mrb_state* mrb, mrb_value self);

mrb_value siren_vec_zero(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_xdir(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_ydir(mrb_state* mrb, mrb_value self);
mrb_value siren_vec_zdir(mrb_state* mrb, mrb_value self);

#endif
