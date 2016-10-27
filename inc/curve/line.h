#ifndef _CURVE_LINE_H_
#define _CURVE_LINE_H_

#include "siren.h"
#include "curve.h"
#include "curve/type.h"

#include <Geom_Line.hxx>

static struct mrb_data_type siren_line_type = { "Line", siren_curve_final };
bool siren_line_install(mrb_state* mrb, struct RClass* mod_siren);

#endif
