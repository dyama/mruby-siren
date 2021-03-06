#ifndef _topalgo_H_
#define _topalgo_H_

#include "siren.h"
#include "vec.h"
#include "shape.h"

#include <BRepBuilderAPI.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>

#include <GeomAPI_Interpolate.hxx> // curve
#include <TColgp_Array1OfVec.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TColStd_HArray1OfBoolean.hxx>

#include <TopExp_Explorer.hxx>

// copy
#include <BRepBuilderAPI_Copy.hxx>

// NURBS curve
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <Geom_BSplineCurve.hxx>

#include <GProp_GProps.hxx>
#include <BRepGProp.hxx>

#include <gp_Circ.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeCircle.hxx>

bool siren_topalgo_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_topalgo_copy     (mrb_state* mrb, mrb_value self);

mrb_value siren_topalgo_line       (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_infline    (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_polyline   (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_interpolate(mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_arc        (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_arc3p      (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_circle     (mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_circle3p   (mrb_state* mrb, mrb_value self);

mrb_value siren_topalgo_volume(mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_cog(mrb_state* mrb, mrb_value self);
mrb_value siren_topalgo_area(mrb_state* mrb, mrb_value self);

#endif
