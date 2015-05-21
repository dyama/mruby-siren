#ifndef _STL_H_
#define _STL_H_

#include "siren.h"
#include "vec.h"
#include "shape.h"

#include <StlAPI.hxx>

bool siren_stl_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_stl_save(mrb_state* mrb, mrb_value self);
mrb_value siren_stl_load(mrb_state* mrb, mrb_value self);

#endif
