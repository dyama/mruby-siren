#ifndef _CURVE_BEZIERCURVE_H_
#define _CURVE_BEZIERCURVE_H_

#include "siren.h"

#include <Geom_BezierCurve.hxx>

static struct mrb_data_type siren_bzcurve_type = { "BzCurve", siren_curve_final };
bool siren_bzcurve_install(mrb_state* mrb, struct RClass* mod_siren);
handle<Geom_BezierCurve> siren_bzcurve_get(mrb_state* mrb, mrb_value self);
mrb_value siren_bzcurve_new(mrb_state* mrb, const handle<Geom_Curve>* curve);

mrb_value siren_bzcurve_init(mrb_state* mrb, mrb_value self);

#endif
