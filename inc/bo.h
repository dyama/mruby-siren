#ifndef _BO_H_
#define _BO_H_

#include "siren.h"
#include "shape.h"

#include <BRepAlgoAPI_BooleanOperation.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>

#include <BRepProj_Projection.hxx>

bool siren_bo_install(mrb_state* mrb, struct RClass* mod_siren);
mrb_value siren_bo_common   (mrb_state* mrb, mrb_value self);
mrb_value siren_bo_fuse     (mrb_state* mrb, mrb_value self);
mrb_value siren_bo_cut      (mrb_state* mrb, mrb_value self);
mrb_value siren_bo_projwire (mrb_state* mrb, mrb_value self);

#endif
