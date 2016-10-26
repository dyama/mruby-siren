#ifndef _CURVE_BSPLINECURVE_H_
#define _CURVE_BSPLINECURVE_H_

#include "siren.h"
#include "curve/type.h"

#include <Geom_BSplineCurve.hxx>

void siren_bsplinecurve_install(mrb_state* mrb, RObject* o);
Handle(Geom_BSplineCurve) siren_bsplinecurve_get(mrb_state* mrb, mrb_value self);

#endif
