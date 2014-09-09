#ifndef _CURVE_H_
#define _CURVE_H_

#include "siren.h"
#include "shape.h"

#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>

#include <TopExp_Explorer.hxx>
#include <BRepAdaptor_Curve.hxx>

bool siren_curve_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_curve_endpts(mrb_state* mrb, mrb_value self);

#endif
