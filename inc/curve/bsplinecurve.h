#ifndef _CURVE_BSPLINECURVE_H_
#define _CURVE_BSPLINECURVE_H_

#include "siren.h"

#include <Geom_BSplineCurve.hxx>

static struct mrb_data_type siren_bsplinecurve_type = { "BSplineCurve", siren_curve_final };
bool siren_bsplinecurve_install(mrb_state* mrb, struct RClass* mod_siren);
Handle(Geom_BSplineCurve) siren_bsplinecurve_get(mrb_state* mrb, mrb_value self);
mrb_value siren_bsplinecurve_new(mrb_state* mrb, const Handle(Geom_Curve)* curve);

#endif
