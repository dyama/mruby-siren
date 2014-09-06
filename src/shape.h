#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "siren.h"
#include "vec.h"
#include "trans.h"

#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_CompSolid.hxx>
#include <TopoDS_Compound.hxx>

TopoDS_Compound*  siren_occ_compound_new(mrb_state* mrb);
TopoDS_CompSolid* siren_occ_compsolid_new(mrb_state* mrb);
TopoDS_Solid*     siren_occ_solid_new(mrb_state* mrb);
TopoDS_Shell*     siren_occ_shell_new(mrb_state* mrb);
TopoDS_Face*      siren_occ_face_new(mrb_state* mrb);
TopoDS_Wire*      siren_occ_wire_new(mrb_state* mrb);
TopoDS_Edge*      siren_occ_edge_new(mrb_state* mrb);
TopoDS_Vertex*    siren_occ_vertex_new(mrb_state* mrb);
TopoDS_Shape*     siren_occ_shape_new(mrb_state* mrb);

void siren_shape_final(mrb_state* mrb, void* p);
bool siren_shape_install(mrb_state* mrb, struct RClass* rclass);
static struct mrb_data_type siren_shape_type = { "Shape", siren_shape_final };
TopoDS_Shape* siren_shape_get(mrb_state* mrb, mrb_value obj);

// mrb_value siren_shape_new(mrb_state* mrb, const TopoDS_Shape* shape);
mrb_value siren_shape_new(mrb_state* mrb, const TopoDS_Shape& shape);

mrb_value siren_shape_init(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_to_s(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_is_null(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_shapetype(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_location(mrb_state* mrb, mrb_value self);

mrb_value siren_shape_translate(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_rotate(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_scale(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_mirror(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_move(mrb_state* mrb, mrb_value self);

#endif
