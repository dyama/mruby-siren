#ifndef _CURVE_OFFSETCURVE_H_
#define _CURVE_OFFSETCURVE_H_

#include "siren.h"

#include <Geom_OffsetCurve.hxx>

static struct mrb_data_type siren_offsetcurve_type = { "OffsetCurve", siren_curve_final };
bool siren_offsetcurve_install(mrb_state* mrb, struct RClass* mod_siren);
handle<Geom_OffsetCurve> siren_offsetcurve_get(mrb_state* mrb, mrb_value self);
mrb_value siren_offsetcurve_new(mrb_state* mrb, const handle<Geom_Curve>* curve);

#endif
