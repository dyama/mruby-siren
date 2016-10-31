#ifndef _SHAPE_VERTEX_H_
#define _SHAPE_VERTEX_H_

#include "siren.h"

#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>

static struct mrb_data_type siren_vertex_type = { "Vertex", siren_shape_final };
bool siren_vertex_install(mrb_state* mrb, struct RClass* mod_siren);
TopoDS_Vertex siren_vertex_get(mrb_state* mrb, mrb_value self);
mrb_value siren_vertex_new(mrb_state* mrb, const TopoDS_Shape* src);
mrb_value siren_vertex_obj(mrb_state* mrb);

mrb_value siren_vertex_xyz(mrb_state* mrb, mrb_value self);
mrb_value siren_vertex_to_v(mrb_state* mrb, mrb_value self);

#endif
