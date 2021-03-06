#ifndef _CURVE_LINE_H_
#define _CURVE_LINE_H_

#include "siren.h"

#include <Geom_Line.hxx>

static struct mrb_data_type siren_line_type = { "Line", siren_curve_final };
bool siren_line_install(mrb_state* mrb, struct RClass* mod_siren);
handle<Geom_Line> siren_line_get(mrb_state* mrb, mrb_value self);
mrb_value siren_line_new(mrb_state* mrb, const handle<Geom_Curve>* curve);

mrb_value siren_line_dir(mrb_state* mrb, mrb_value self);

#endif
