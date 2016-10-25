#include "siren.h"
#include "curve/type.h"

SrCT_CurveType siren_curve_geomtype_native(Handle(Geom_Curve) hgc)
{
  //if (!Handle(Geom_BoundedCurve)::DownCast(hgc).IsNull()) {
    if (!Handle(Geom_BezierCurve)::DownCast(hgc).IsNull()) {
      return SrCT_BEZIERCURVE;
    }
    if (!Handle(Geom_BSplineCurve)::DownCast(hgc).IsNull()) {
      return SrCT_BSPLINECURVE;
    }
    if (!Handle(Geom_TrimmedCurve)::DownCast(hgc).IsNull()) {
      return SrCT_TRIMMEDCURVE;
    }
  //  return SrCT_BOUNDEDCURVE;
  //}
  //if (!Handle(Geom_Conic)::DownCast(hgc).IsNull()) {
    if (!Handle(Geom_Circle)::DownCast(hgc).IsNull()) {
      return SrCT_CIRCLE;
    }
    if (!Handle(Geom_Ellipse)::DownCast(hgc).IsNull()) {
      return SrCT_ELLIPSE;
    }
    if (!Handle(Geom_Hyperbola)::DownCast(hgc).IsNull()) {
      return SrCT_HYPERBOLA;
    }
    if (!Handle(Geom_Parabola)::DownCast(hgc).IsNull()) {
      return SrCT_PARABOLA;
    }
  //  return SrCT_CONIC;
  //}
  if (!Handle(Geom_Line)::DownCast(hgc).IsNull()) {
    return SrCT_LINE;
  }
  if (!Handle(Geom_OffsetCurve)::DownCast(hgc).IsNull()) {
    return SrCT_OFFSETCURVE;
  }
  if (!Handle(ShapeExtend_ComplexCurve)::DownCast(hgc).IsNull()) {
    return SrCT_COMPLEXCURVE;
  }
  return SrCT_UNKNOWN;
}
