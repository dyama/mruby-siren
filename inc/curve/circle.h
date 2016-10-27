#ifndef _CURVE_CIRCLE_H_
#define _CURVE_CIRCLE_H_

#include "siren.h"

#include <Geom_Circle.hxx>

static struct mrb_data_type siren_circle_type = { "Circle", siren_curve_final };
bool siren_circle_install(mrb_state* mrb, struct RClass* mod_siren);
opencascade::handle<Geom_Circle> siren_circle_get(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_new(mrb_state* mrb, const opencascade::handle<Geom_Curve>* curve);

mrb_value siren_circle_radius(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_radius_set(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_center(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_center_set(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_area(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_length(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_normal(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_normal_set(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_dir(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_dir_set(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_dist(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_distdist(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_contain(mrb_state* mrb, mrb_value self);

#endif
