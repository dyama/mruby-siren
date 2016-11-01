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
#include "curve/bzcurve.h"
#include "curve/bscurve.h"
#include "curve/offsetcurve.h"

inline GeomAbs_CurveType siren_curve_geomtype_native(opencascade::handle<Geom_Curve> hgc)
{
  opencascade::handle<Standard_Type> type = hgc->DynamicType();
  /* Geom_BoundedCurve */
  if (STANDARD_TYPE(Geom_BezierCurve) == type)  { return GeomAbs_BezierCurve; }
  if (STANDARD_TYPE(Geom_BSplineCurve) == type) { return GeomAbs_BSplineCurve; }
  /* Geom_Conic */
  if (STANDARD_TYPE(Geom_Circle) == type)       { return GeomAbs_Circle; }
  if (STANDARD_TYPE(Geom_Ellipse) == type)      { return GeomAbs_Ellipse; }
  if (STANDARD_TYPE(Geom_Hyperbola) == type)    { return GeomAbs_Hyperbola; }
  if (STANDARD_TYPE(Geom_Parabola) == type)     { return GeomAbs_Parabola; }
  /* Line */
  if (STANDARD_TYPE(Geom_Line) == type)         { return GeomAbs_Line; }
  return GeomAbs_OtherCurve;
}

bool siren_curve_install(mrb_state* mrb, struct RClass* rclass);
opencascade::handle<Geom_Curve>* siren_curve_get(mrb_state* mrb, mrb_value obj);
struct RClass* siren_curve_rclass(mrb_state* mrb);

mrb_value siren_curve_new(mrb_state* mrb, const opencascade::handle<Geom_Curve>* curve);
mrb_value siren_curve_init(mrb_state* mrb, mrb_value self);

#endif
