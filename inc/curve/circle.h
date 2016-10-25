#ifndef _CURVE_CIRCLE_H_
#define _CURVE_CIRCLE_H_

#include "siren.h"
#include "curve/type.h"

#include <Geom_Circle.hxx>

void siren_circle_install(mrb_state* mrb, RObject* o);
mrb_value siren_circle_radius(mrb_state* mrb, mrb_value self);
mrb_value siren_circle_radius_set(mrb_state* mrb, mrb_value self);

#endif
