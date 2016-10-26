#ifndef _CURVE_ELLIPSE_H_
#define _CURVE_ELLIPSE_H_

#include "siren.h"
#include "curve/type.h"

#include <Geom_Ellipse.hxx>

void siren_ellipse_install(mrb_state* mrb, RObject* o);
Handle(Geom_Ellipse) siren_ellipse_get(mrb_state* mrb, mrb_value self);

#endif
