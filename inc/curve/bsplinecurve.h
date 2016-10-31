#ifndef _CURVE_BSPLINECURVE_H_
#define _CURVE_BSPLINECURVE_H_

#include "siren.h"

#include <Geom_BSplineCurve.hxx>

static struct mrb_data_type siren_bsplinecurve_type = { "BSplineCurve", siren_curve_final };
bool siren_bsplinecurve_install(mrb_state* mrb, struct RClass* mod_siren);
opencascade::handle<Geom_BSplineCurve> siren_bsplinecurve_get(mrb_state* mrb, mrb_value self);
mrb_value siren_bsplinecurve_new(mrb_state* mrb, const opencascade::handle<Geom_Curve>* curve);

mrb_value siren_bsplinecurve_init(mrb_state* mrb, mrb_value self);
mrb_value siren_bsplinecurve_degree(mrb_state* mrb, mrb_value self);
mrb_value siren_bsplinecurve_knots(mrb_state* mrb, mrb_value self);
mrb_value siren_bsplinecurve_mults(mrb_state* mrb, mrb_value self);
mrb_value siren_bsplinecurve_poles(mrb_state* mrb, mrb_value self);
mrb_value siren_bsplinecurve_weights(mrb_state* mrb, mrb_value self);

#endif
