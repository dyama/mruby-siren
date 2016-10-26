#ifndef _CURVE_HYPERBOLA_H_
#define _CURVE_HYPERBOLA_H_

#include "siren.h"
#include "curve/type.h"

#include <Geom_Hyperbola.hxx>

void siren_hyperbola_install(mrb_state* mrb, RObject* o);
Handle(Geom_Hyperbola) siren_hyperbola_get(mrb_state* mrb, mrb_value self);

#endif
