#ifndef _CURVE_PARABOLA_H_
#define _CURVE_PARABOLA_H_

#include "siren.h"

#include <Geom_Parabola.hxx>

static struct mrb_data_type siren_parabola_type = { "Palabora", siren_curve_final };
bool siren_parabola_install(mrb_state* mrb, struct RClass* mod_siren);
handle<Geom_Parabola> siren_parabola_get(mrb_state* mrb, mrb_value self);
mrb_value siren_parabola_new(mrb_state* mrb, const handle<Geom_Curve>* curve);

#endif
