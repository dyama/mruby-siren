#ifndef _BREPIO_H_
#define _BREPIO_H_

#include "siren.h"
#include "vec.h"
#include "shape.h"

#include <BRepTools.hxx>
#include <BRep_Builder.hxx>

bool siren_brepio_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_brepio_save(mrb_state* mrb, mrb_value self);
mrb_value siren_brepio_load(mrb_state* mrb, mrb_value self);

#endif
