/**
 * trimmedcurve.cpp
 * Implementation of singleton methods for TRIMMEDCURVE
 */

#include "curve/trimmedcurve.h"

Handle(Geom_TrimmedCurve) siren_trimmedcurve_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_TrimmedCurve) trimmedcurve = Handle(Geom_TrimmedCurve)::DownCast(hgc);
  if (trimmedcurve.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The curve type is not TRIMMEDCURVE.");
  }
  return trimmedcurve;
}

void siren_trimmedcurve_install(mrb_state* mrb, RObject* o)
{
  return;
}
