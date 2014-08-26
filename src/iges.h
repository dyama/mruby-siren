#ifndef _IGES_H_
#define _IGES_H_

#include "siren.h"
#include "vec.h"
#include "shape.h"

bool siren_iges_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_iges_save(mrb_state* mrb, mrb_value self);
mrb_value siren_iges_load(mrb_state* mrb, mrb_value self);

#endif
