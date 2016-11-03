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

static struct mrb_data_type siren_wire_type = { "Wire", siren_shape_final };
bool siren_wire_install(mrb_state* mrb, struct RClass* mod_siren);
TopoDS_Wire siren_wire_get(mrb_state* mrb, mrb_value self);
mrb_value siren_wire_new(mrb_state* mrb, const TopoDS_Shape* src);
mrb_value siren_wire_obj(mrb_state* mrb);
struct RClass* siren_wire_rclass(mrb_state* mrb);

mrb_value siren_wire_make(mrb_state* mrb, mrb_value self);
mrb_value siren_wire_ordered_edges(mrb_state* mrb, mrb_value self);
mrb_value siren_wire_curves(mrb_state* mrb, mrb_value self);

#endif
