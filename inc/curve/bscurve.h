#ifndef _CURVE_BSPLINECURVE_H_
#define _CURVE_BSPLINECURVE_H_

#include "siren.h"

#include <Geom_BSplineCurve.hxx>

static struct mrb_data_type siren_bscurve_type = { "BSCurve", siren_curve_final };
bool siren_bscurve_install(mrb_state* mrb, struct RClass* mod_siren);
handle<Geom_BSplineCurve> siren_bscurve_get(mrb_state* mrb, mrb_value self);
mrb_value siren_bscurve_new(mrb_state* mrb, const handle<Geom_Curve>* curve);

mrb_value siren_bscurve_init(mrb_state* mrb, mrb_value self);
mrb_value siren_bscurve_degree(mrb_state* mrb, mrb_value self);
mrb_value siren_bscurve_knots(mrb_state* mrb, mrb_value self);
mrb_value siren_bscurve_mults(mrb_state* mrb, mrb_value self);
mrb_value siren_bscurve_poles(mrb_state* mrb, mrb_value self);
mrb_value siren_bscurve_weights(mrb_state* mrb, mrb_value self);

#endif
