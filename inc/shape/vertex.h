#ifndef _SHAPE_VERTEX_H_
#define _SHAPE_VERTEX_H_

#include "siren.h"

#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>

void siren_vertex_install(mrb_state* mrb, RObject* o);

mrb_value siren_vertex_xyz(mrb_state* mrb, mrb_value self);
mrb_value siren_vertex_to_v(mrb_state* mrb, mrb_value self);

#endif
