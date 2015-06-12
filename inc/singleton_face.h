#ifndef _SINGLETON_FACE_H_
#define _SINGLETON_FACE_H_

#include "siren.h"
#include "shape.h"
#include "build.h"
#include "vec.h"

#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>

#include <BRepTools.hxx>
#include <GeomLProp_SLProps.hxx>

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

void siren_face_install(mrb_state* mrb, RObject* o);

mrb_value siren_face_normal(mrb_state* mrb, mrb_value self);
mrb_value siren_face_to_bezier(mrb_state* mrb, mrb_value self);
mrb_value siren_face_split(mrb_state* mrb, mrb_value self);
mrb_value siren_face_triangle(mrb_state* mrb, mrb_value self);

#endif
