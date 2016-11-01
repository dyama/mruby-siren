#ifndef _CURVE_ELLIPSE_H_
#define _CURVE_ELLIPSE_H_

#include "siren.h"

#include <Geom_Ellipse.hxx>

static struct mrb_data_type siren_ellipse_type = { "Ellipse", siren_curve_final };
bool siren_ellipse_install(mrb_state* mrb, struct RClass* mod_siren);
handle<Geom_Ellipse> siren_ellipse_get(mrb_state* mrb, mrb_value self);
mrb_value siren_ellipse_new(mrb_state* mrb, const handle<Geom_Curve>* curve);

#endif
