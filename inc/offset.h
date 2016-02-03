#ifndef _OFFSET_H_
#define _OFFSET_H_

#include "siren.h"
#include "shape.h"
#include "build.h"

// sweep_vec
#include <BRepOffsetAPI_MakePipe.hxx>

// sweep_path
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepAdaptor_CompCurve.hxx>
#include <TopExp.hxx>
#include <Law_S.hxx>

// loft
#include <BRepOffsetAPI_ThruSections.hxx>

// offset
#include <Geom_OffsetSurface.hxx>
#include <BRepOffset_MakeOffset.hxx>
#include <BRepOffsetAPI_MakeOffsetShape.hxx>

bool siren_offset_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_offset_sweep_vec(mrb_state* mrb, mrb_value self);
mrb_value siren_offset_sweep_path(mrb_state* mrb, mrb_value self);
mrb_value siren_offset_loft(mrb_state* mrb, mrb_value self);
mrb_value siren_offset_offset_geomsurf(mrb_state* mrb, mrb_value self);
mrb_value siren_offset_offset(mrb_state* mrb, mrb_value self);
mrb_value siren_offset_offset_shape(mrb_state* mrb, mrb_value self);
mrb_value siren_offset_pipe(mrb_state* mrb, mrb_value self);

#endif
