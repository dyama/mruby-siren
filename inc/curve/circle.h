#ifndef _CURVE_CIRCLE_H_
#define _CURVE_CIRCLE_H_

#include "siren.h"
#include "curve/type.h"

#include <Geom_Circle.hxx>

void siren_circle_install(mrb_state* mrb, RObject* o);
Handle(Geom_Circle) siren_circle_get(mrb_state* mrb, mrb_value self);

mrb_value siren_circle_radius(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_radius_set(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_center(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_center_set(mrb_state* mrb, mrb_value self);
// mrb_value siren_circle_area(mrb_state* mrb, mrb_value self);
// mrb_value siren_circle_axis(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_length(mrb_state* mrb, mrb_value self);

#endif
