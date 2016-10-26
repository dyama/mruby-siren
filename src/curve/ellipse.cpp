/**
 * ellipse.cpp
 * Implementation of singleton methods for ELLIPSE
 */

#include "curve/ellipse.h"

Handle(Geom_Ellipse) siren_ellipse_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_Ellipse) ellipse = Handle(Geom_Ellipse)::DownCast(hgc);
  if (ellipse.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The curve type is not ELLIPSE.");
  }
  return ellipse;
}

void siren_ellipse_install(mrb_state* mrb, RObject* o)
{
  return;
}
