#include "siren.h"
#include "curve/type.h"

GeomAbs_CurveType siren_curve_geomtype_native(Handle(Geom_Curve) hgc)
{
  Handle(Standard_Type) type = hgc->DynamicType();
  /* Geom_BoundedCurve */
  if (STANDARD_TYPE(Geom_BezierCurve) == type) {
    return GeomAbs_BezierCurve;
  }
  if (STANDARD_TYPE(Geom_BSplineCurve) == type) {
    return GeomAbs_BSplineCurve;
  }
  /* Geom_Conic */
  if (STANDARD_TYPE(Geom_Circle) == type) {
    return GeomAbs_Circle;
  }
  if (STANDARD_TYPE(Geom_Ellipse) == type) {
    return GeomAbs_Ellipse;
  }
  if (STANDARD_TYPE(Geom_Hyperbola) == type) {
    return GeomAbs_Hyperbola;
  }
  if (STANDARD_TYPE(Geom_Parabola) == type) {
    return GeomAbs_Parabola;
  }
  /* Line */
  if (STANDARD_TYPE(Geom_Line) == type) {
    return GeomAbs_Line;
  }
  return GeomAbs_OtherCurve;
}
