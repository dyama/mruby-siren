#ifndef _SHAPE_WIRE_H_
#define _SHAPE_WIRE_H_

#include "siren.h"
#include "shape.h"
#include "topalgo.h"
#include "vec.h"

#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Edge.hxx>

#include <BRepTools_WireExplorer.hxx>

void siren_wire_install(mrb_state* mrb, RObject* o);

mrb_value siren_wire_ordered_edges(mrb_state* mrb, mrb_value self);
mrb_value siren_wire_curves(mrb_state* mrb, mrb_value self);

#endif
