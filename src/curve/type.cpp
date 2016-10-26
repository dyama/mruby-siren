#include "siren.h"
#include "curve/type.h"

SrCT_CurveType siren_curve_geomtype_native(Handle(Geom_Curve) hgc)
{
  Handle(Standard_Type) type = hgc->DynamicType();
  /* Geom_BoundedCurve */
  if (STANDARD_TYPE(Geom_BezierCurve) == type) {
    return SrCT_BEZIERCURVE;
  }
  if (STANDARD_TYPE(Geom_BSplineCurve) == type) {
    return SrCT_BSPLINECURVE;
  }
  if (STANDARD_TYPE(Geom_TrimmedCurve) == type) {
    return SrCT_TRIMMEDCURVE;
  }
  /* Geom_Conic */
  if (STANDARD_TYPE(Geom_Circle) == type) {
    return SrCT_CIRCLE;
  }
  if (STANDARD_TYPE(Geom_Ellipse) == type) {
    return SrCT_ELLIPSE;
  }
  if (STANDARD_TYPE(Geom_Hyperbola) == type) {
    return SrCT_HYPERBOLA;
  }
  if (STANDARD_TYPE(Geom_Parabola) == type) {
    return SrCT_PARABOLA;
  }
  /* Other */
  if (STANDARD_TYPE(Geom_Line) == type) {
    return SrCT_LINE;
  }
  if (STANDARD_TYPE(Geom_OffsetCurve) == type) {
    return SrCT_OFFSETCURVE;
  }
  if (STANDARD_TYPE(ShapeExtend_ComplexCurve) == type) {
    return SrCT_COMPLEXCURVE;
  }
  return SrCT_UNKNOWN;
}
