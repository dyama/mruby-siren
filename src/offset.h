#ifndef _OFFSET_H_
#define _OFFSET_H_

#include "siren.h"
#include "shape.h"
#include "build.h"
#include "exp.h"

#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepAdaptor_CompCurve.hxx>
#include <TopExp.hxx>
#include <Law_S.hxx>

bool siren_offset_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_offset_sweep_vec(mrb_state* mrb, mrb_value self);
mrb_value siren_offset_sweep_path(mrb_state* mrb, mrb_value self);

#endif
