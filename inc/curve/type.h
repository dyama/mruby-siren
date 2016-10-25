#ifndef _CURVE_TYPE_H_
#define _CURVE_TYPE_H_

enum SrCT_CurveType {
  SrCT_UNKNOWN      = 0,
  SrCT_BEZIERCURVE  = 1,
  SrCT_BSPLINECURVE = 2,
  SrCT_TRIMMEDCURVE = 3,
  SrCT_BOUNDEDCURVE = 4,
  SrCT_CIRCLE       = 5,
  SrCT_ELLIPSE      = 6,
  SrCT_HYPERBOLA    = 7,
  SrCT_PARABOLA     = 8,
  SrCT_CONIC        = 9,
  SrCT_LINE         = 10,
  SrCT_OFFSETCURVE  = 11,
  SrCT_COMPLEXCURVE = 12
};

#endif
