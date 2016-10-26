/**
 * line.cpp
 * Implementation of singleton methods for LINE
 */

#include "curve/line.h"

Handle(Geom_Line) siren_line_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_Line) line = Handle(Geom_Line)::DownCast(hgc);
  if (line.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The curve type is not LINE.");
  }
  return line;
}

void siren_line_install(mrb_state* mrb, RObject* o)
{
  return;
}
