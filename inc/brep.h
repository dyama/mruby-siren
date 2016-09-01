#ifndef _BREP_H_
#define _BREP_H_

#include "siren.h"
#include "vec.h"
#include "shape.h"

#include <BRepTools.hxx>
#include <BRep_Builder.hxx>

bool siren_brep_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_brep_save(mrb_state* mrb, mrb_value self);
mrb_value siren_brep_load(mrb_state* mrb, mrb_value self);
mrb_value siren_brep_dump(mrb_state* mrb, mrb_value self);

#endif
