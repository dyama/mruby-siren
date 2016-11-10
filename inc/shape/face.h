#ifndef _SHAPE_FACE_H_
#define _SHAPE_FACE_H_

#include "siren.h"
#include "shape.h"
#include "vec.h"

#include <gp_Ax3.hxx>
#include <gp_Pln.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>

#include <BRepTools.hxx>
#include <GeomLProp_SLProps.hxx>

#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>

#include <Geom_BezierSurface.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_Array2OfReal.hxx>

#include <Geom_BSplineSurface.hxx>
#include <ShapeFix_Shape.hxx>

// to_bezier
#include <TopoDS_Compound.hxx>
#include <BRep_Tool.hxx>
#include <Geom_Surface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_BezierSurface.hxx>
#include <GeomConvert_BSplineSurfaceToBezierSurface.hxx>
#include <TColGeom_Array2OfBezierSurface.hxx>

// split
#include <BRepFeat_SplitShape.hxx>

// triangle
#include <BRepMesh_IncrementalMesh.hxx>
#include <Poly_Triangulation.hxx>
#include <Poly_Triangle.hxx>
#include <Poly_Array1OfTriangle.hxx>

static struct mrb_data_type siren_face_type = { "Face", siren_shape_final };
bool siren_face_install(mrb_state* mrb, struct RClass* mod_siren);
TopoDS_Face siren_face_get(mrb_state* mrb, mrb_value self);
mrb_value siren_face_new(mrb_state* mrb, const TopoDS_Shape* src);
mrb_value siren_face_obj(mrb_state* mrb);
struct RClass* siren_face_rclass(mrb_state* mrb);

mrb_value siren_face_plane(mrb_state* mrb, mrb_value self);
mrb_value siren_face_face(mrb_state* mrb, mrb_value self);
mrb_value siren_face_infplane(mrb_state* mrb, mrb_value self);
mrb_value siren_face_polygon(mrb_state* mrb, mrb_value self);
mrb_value siren_face_bzsurf(mrb_state* mrb, mrb_value self);
mrb_value siren_face_bssurf(mrb_state* mrb, mrb_value self);

mrb_value siren_face_normal(mrb_state* mrb, mrb_value self);
mrb_value siren_face_to_bezier(mrb_state* mrb, mrb_value self);
mrb_value siren_face_split(mrb_state* mrb, mrb_value self);
mrb_value siren_face_triangle(mrb_state* mrb, mrb_value self);

#endif
