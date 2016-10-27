/**
 * parabola.cpp
 * Implementation of singleton methods for PARABOLA
 */

#include "curve/parabola.h"

Handle(Geom_Parabola) siren_parabola_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_Parabola) parabola = Handle(Geom_Parabola)::DownCast(hgc);
  if (parabola.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The curve type is not PARABOLA.");
  }
  return parabola;
}

bool siren_parabola_install(mrb_state* mrb, struct RClass* mod_siren)
{
  return true;
}
