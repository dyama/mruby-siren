#ifndef _WIRE_H_
#define _WIRE_H_

#include "siren.h"
#include "shape.h"
#include "build.h"
#include "vec.h"

#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Edge.hxx>

#include <BRepTools_WireExplorer.hxx>

void siren_wire_install(mrb_state* mrb, RObject* o);

mrb_value siren_wire_ordered_edges(mrb_state* mrb, mrb_value self);

#endif
