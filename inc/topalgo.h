#ifndef _topalgo_H_
#define _topalgo_H_

#include "siren.h"
#include "vec.h"
#include "shape.h"

#include <BRep_Builder.hxx>
#include <BRepBuilderAPI.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>

#include <GeomAPI_Interpolate.hxx> // curve
#include <TColgp_Array1OfVec.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TColStd_HArray1OfBoolean.hxx>

#include <gp_Ax3.hxx> // plane
#include <gp_Pln.hxx>

#include <ShapeFix_Wire.hxx> // wire
#include <TopExp_Explorer.hxx>
#include <ShapeExtend_WireData.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <ShapeFix_ShapeTolerance.hxx>

// copy
#include <BRepBuilderAPI_Copy.hxx>

// NURBS curve
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <Geom_BSplineCurve.hxx>

// Bezier surface
#include <Geom_BezierSurface.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_Array2OfReal.hxx>

// NURBS surface
#include <Geom_BSplineSurface.hxx>
#include <ShapeFix_Shape.hxx>

// sewing
#include <BRepBuilderAPI_Sewing.hxx>

#include <GProp_GProps.hxx>
#include <BRepGProp.hxx>

#include <gp_Circ.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeCircle.hxx>

bool siren_topalgo_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_topalgo_copy     (mrb_state* mrb, mrb_value self);

mrb_value siren_topalgo_vertex   (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_line     (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_infline  (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_polyline (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_curve    (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_wire     (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_arc      (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_arc3p    (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_circle   (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_circle3p (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_plane    (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_face     (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_infplane (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_polygon  (mrb_state* mrb, mrb_value self);

// mrb_value siren_topalgo_beziercurve(mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_nurbscurve(mrb_state* mrb, mrb_value self);
// mrb_value siren_topalgo_rectangle(mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_beziersurf(mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_nurbssurf(mrb_state* mrb, mrb_value self);
// mrb_value siren_topalgo_shell(mrb_state* mrb, mrb_value self);

mrb_value siren_topalgo_sewing(mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_solid(mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_compound(mrb_state* mrb, mrb_value self);

// Instance methods for Siren::Shape class.
mrb_value siren_topalgo_volume(mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_cog(mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_area(mrb_state* mrb, mrb_value self);

#endif
