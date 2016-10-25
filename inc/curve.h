#ifndef _CURVE_H_
#define _CURVE_H_

#include "siren.h"
#include "curve/type.h"

#include <Geom_BoundedCurve.hxx>
#include   <Geom_BezierCurve.hxx>
#include   <Geom_BSplineCurve.hxx>
#include   <Geom_TrimmedCurve.hxx>
#include <Geom_Conic.hxx>
#include   <Geom_Ellipse.hxx>
#include   <Geom_Hyperbola.hxx>
#include   <Geom_Parabola.hxx>
#include <Geom_OffsetCurve.hxx>
#include <ShapeExtend_ComplexCurve.hxx>

#include "curve/circle.h"
#include "curve/line.h"

void siren_curve_final(mrb_state* mrb, void* p);
bool siren_curve_install(mrb_state* mrb, struct RClass* rclass);
static struct mrb_data_type siren_curve_type = { "Curve", siren_curve_final };
Handle(Geom_Curve)* siren_curve_get(mrb_state* mrb, mrb_value obj);
struct RClass* siren_curve_rclass(mrb_state* mrb);
void siren_curve_add_singleton_method(mrb_state* mrb, mrb_value& self);

mrb_value siren_curve_new(mrb_state* mrb, const Handle(Geom_Curve)* curve);
mrb_value siren_curve_init(mrb_state* mrb, mrb_value self);
mrb_value siren_curve_to_s(mrb_state* mrb, mrb_value self);

mrb_value siren_curve_geomtype(mrb_state* mrb, mrb_value self);

#endif
