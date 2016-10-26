#ifndef _CURVE_BEZIERCURVE_H_
#define _CURVE_BEZIERCURVE_H_

#include "siren.h"
#include "curve/type.h"

#include <Geom_BezierCurve.hxx>

void siren_beziercurve_install(mrb_state* mrb, RObject* o);
Handle(Geom_BezierCurve) siren_beziercurve_get(mrb_state* mrb, mrb_value self);

#endif
