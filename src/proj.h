#ifndef _PROJ_H_
#define _PROJ_H_

#include "siren.h"
#include "shape.h"

#include <BRepProj_Projection.hxx>

bool siren_proj_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_proj_wire(mrb_state* mrb, mrb_value self);

#endif
