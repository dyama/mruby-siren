#ifndef _CURVE_HYPERBOLA_H_
#define _CURVE_HYPERBOLA_H_

#include "siren.h"

#include <Geom_Hyperbola.hxx>

static struct mrb_data_type siren_hyperbola_type = { "Hyperbola", siren_curve_final };
bool siren_hyperbola_install(mrb_state* mrb, struct RClass* mod_siren);
Handle(Geom_Hyperbola) siren_hyperbola_get(mrb_state* mrb, mrb_value self);
mrb_value siren_hyperbola_new(mrb_state* mrb, const Handle(Geom_Curve)* curve);

#endif
