/**
 * beziercurve.cpp
 * Implementation of singleton methods for BEZIERCURVE
 */

#include "curve/beziercurve.h"

Handle(Geom_BezierCurve) siren_beziercurve_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_BezierCurve) beziercurve = Handle(Geom_BezierCurve)::DownCast(hgc);
  if (beziercurve.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The curve type is not BEZIERCURVE.");
  }
  return beziercurve;
}

bool siren_beziercurve_install(mrb_state* mrb, struct RClass* mod_siren)
{
  return true;
}
