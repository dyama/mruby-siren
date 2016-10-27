/**
 * offsetcurve.cpp
 * Implementation of singleton methods for OFFSETCURVE
 */

#include "curve/offsetcurve.h"

Handle(Geom_OffsetCurve) siren_offsetcurve_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_OffsetCurve) offsetcurve = Handle(Geom_OffsetCurve)::DownCast(hgc);
  if (offsetcurve.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The curve type is not OFFSETCURVE.");
  }
  return offsetcurve;
}

bool siren_offsetcurve_install(mrb_state* mrb, struct RClass* mod_siren)
{
  return true;
}
