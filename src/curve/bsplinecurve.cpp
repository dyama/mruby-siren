/**
 * bsplinecurve.cpp
 * Implementation of singleton methods for BSPLINECURVE
 */

#include "curve/bsplinecurve.h"

Handle(Geom_BSplineCurve) siren_bsplinecurve_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_BSplineCurve) bsplinecurve = Handle(Geom_BSplineCurve)::DownCast(hgc);
  if (bsplinecurve.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The curve type is not BSPLINECURVE.");
  }
  return bsplinecurve;
}

void siren_bsplinecurve_install(mrb_state* mrb, RObject* o)
{
  return;
}
