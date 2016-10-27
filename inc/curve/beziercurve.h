#ifndef _CURVE_BEZIERCURVE_H_
#define _CURVE_BEZIERCURVE_H_

#include "siren.h"

#include <Geom_BezierCurve.hxx>

static struct mrb_data_type siren_beziercurve_type = { "BezierCurve", siren_curve_final };
bool siren_beziercurve_install(mrb_state* mrb, struct RClass* mod_siren);
Handle(Geom_BezierCurve) siren_beziercurve_get(mrb_state* mrb, mrb_value self);
mrb_value siren_beziercurve_new(mrb_state* mrb, const Handle(Geom_Curve)* curve);

#endif
