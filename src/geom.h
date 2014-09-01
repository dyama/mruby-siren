#ifndef _GEOM_H_
#define _GEOM_H_

#include "siren.h"
#include "shape.h"
#include "build.h"

#include <BRep_Tool.hxx>
#include <Geom_Surface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_BezierSurface.hxx>
#include <GeomConvert_BSplineSurfaceToBezierSurface.hxx>
#include <TColGeom_Array2OfBezierSurface.hxx>

bool siren_geom_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_geom_bs2bzsurf(mrb_state* mrb, mrb_value self);

#endif
