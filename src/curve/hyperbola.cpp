/**
 * hyperbola.cpp
 * Implementation of singleton methods for HYPERBOLA
 */

#include "curve/hyperbola.h"

Handle(Geom_Hyperbola) siren_hyperbola_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_Hyperbola) hyperbola = Handle(Geom_Hyperbola)::DownCast(hgc);
  if (hyperbola.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The curve type is not HYPERBOLA.");
  }
  return hyperbola;
}

bool siren_hyperbola_install(mrb_state* mrb, struct RClass* mod_siren)
{
  return true;
}
