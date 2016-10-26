#ifndef _CURVE_OFFSETCURVE_H_
#define _CURVE_OFFSETCURVE_H_

#include "siren.h"
#include "curve/type.h"

#include <Geom_OffsetCurve.hxx>

void siren_offsetcurve_install(mrb_state* mrb, RObject* o);
Handle(Geom_OffsetCurve) siren_offsetcurve_get(mrb_state* mrb, mrb_value self);

#endif
