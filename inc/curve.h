#ifndef _CURVE_H_
#define _CURVE_H_

#include "siren.h"

#include <Geom_Curve.hxx>
#include   <Geom_BoundedCurve.hxx>
#include     <Geom_BezierCurve.hxx>
#include     <Geom_BSplineCurve.hxx>
#include     <Geom_TrimmedCurve.hxx>
#include   <Geom_Conic.hxx>
#include     <Geom_Circle.hxx>
#include     <Geom_Ellipse.hxx>
#include     <Geom_Hyperbola.hxx>
#include     <Geom_Parabola.hxx>
#include   <Geom_Line.hxx>
#include   <Geom_OffsetCurve.hxx>
#include   <ShapeExtend_ComplexCurve.hxx>

enum SrGCT_GeomCurveType {
  SrGCT_UNKNOWN      = 0,
  SrGCT_BEZIERCURVE  = 1,
  SrGCT_BSPLINECURVE = 2,
  SrGCT_TRIMMEDCURVE = 3,
  SrGCT_BOUNDEDCURVE = 4,
  SrGCT_CIRCLE       = 5,
  SrGCT_ELLIPSE      = 6,
  SrGCT_HYPERBOLA    = 7,
  SrGCT_PARABOLA     = 8,
  SrGCT_CONIC        = 9,
  SrGCT_LINE         = 10,
  SrGCT_OFFSETCURVE  = 11,
  SrGCT_COMPLEXCURVE = 12
};

void siren_curve_final(mrb_state* mrb, void* p);
bool siren_curve_install(mrb_state* mrb, struct RClass* rclass);
static struct mrb_data_type siren_curve_type = { "Curve", siren_curve_final };
Handle(Geom_Curve)* siren_curve_get(mrb_state* mrb, mrb_value obj);
struct RClass* siren_curve_rclass(mrb_state* mrb);

SrGCT_GeomCurveType siren_curve_geomtype_native(Handle(Geom_Curve) hgc);

mrb_value siren_curve_new(mrb_state* mrb, const Handle(Geom_Curve)* curve);
mrb_value siren_curve_init(mrb_state* mrb, mrb_value self);
mrb_value siren_curve_to_s(mrb_state* mrb, mrb_value self);

mrb_value siren_curve_geomtype(mrb_state* mrb, mrb_value self);

mrb_value siren_curve_circle_get_radius(mrb_state* mrb, mrb_value self);
mrb_value siren_curve_circle_set_radius(mrb_state* mrb, mrb_value self);

#endif
