/**
 * complexcurve.cpp
 * Implementation of singleton methods for COMPLEXCURVE
 */

#include "curve/complexcurve.h"

Handle(ShapeExtend_ComplexCurve) siren_complexcurve_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(ShapeExtend_ComplexCurve) complexcurve = Handle(ShapeExtend_ComplexCurve)::DownCast(hgc);
  if (complexcurve.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The curve type is not COMPLEXCURVE.");
  }
  return complexcurve;
}

void siren_complexcurve_install(mrb_state* mrb, RObject* o)
{
  return;
}
