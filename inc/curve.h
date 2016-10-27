#ifndef _CURVE_H_
#define _CURVE_H_

#include "siren.h"

#include <GeomAbs_CurveType.hxx>

void siren_curve_final(mrb_state* mrb, void* p);
static struct mrb_data_type siren_curve_type = { "Curve", siren_curve_final };

#include "curve/line.h"
#include "curve/circle.h"
#include "curve/ellipse.h"
#include "curve/hyperbola.h"
#include "curve/parabola.h"
#include "curve/beziercurve.h"
#include "curve/bsplinecurve.h"
#include "curve/offsetcurve.h"

bool siren_curve_install(mrb_state* mrb, struct RClass* rclass);
Handle(Geom_Curve)* siren_curve_get(mrb_state* mrb, mrb_value obj);
struct RClass* siren_curve_rclass(mrb_state* mrb);

mrb_value siren_curve_new(mrb_state* mrb, const Handle(Geom_Curve)* curve);
mrb_value siren_curve_init(mrb_state* mrb, mrb_value self);

#endif
