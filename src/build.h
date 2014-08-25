#ifndef _BUILD_H_
#define _BUILD_H_

#include "siren.h"
#include "vec.h"
#include "shape.h"

#include <BRep_Builder.hxx>
#include <BRepBuilderAPI.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>

bool mrb_siren_build_install(mrb_state* mrb, struct RClass* rclass);

mrb_method(build_vertex);
mrb_method(build_line);

mrb_method(build_compound);
// mrb_method(build_polyline);
// mrb_method(build_polygon);
// mrb_method(build_plane);
// mrb_method(build_nurbssurf);
// mrb_method(build_nurbscurve);
// mrb_method(build_curve);
// mrb_method(build_sew);
// mrb_method(build_solid);

#endif
