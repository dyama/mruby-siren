#ifndef _BOOL_H_
#define _BOOL_H_

#include "siren.h"
#include "shape.h"

#include <BRepAlgoAPI_Common.hxx>
#include <BRepProj_Projection.hxx>

bool siren_bool_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_bool_common   (mrb_state* mrb, mrb_value self);
mrb_value siren_bool_fuse     (mrb_state* mrb, mrb_value self);
mrb_value siren_bool_cut      (mrb_state* mrb, mrb_value self);
mrb_value siren_bool_projwire (mrb_state* mrb, mrb_value self);

#endif
