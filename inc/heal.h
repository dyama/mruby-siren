#ifndef _HEAL_H_
#define _HEAL_H_

#include "siren.h"
#include "shape.h"

#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>

#include <ShapeFix_Shape.hxx>

#include <ShapeAnalysis.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>

bool siren_heal_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_heal_outerwire(mrb_state* mrb, mrb_value self);
mrb_value siren_heal_fix(mrb_state* mrb, mrb_value self);

#endif
