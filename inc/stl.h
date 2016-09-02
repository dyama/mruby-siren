#ifndef _STL_H_
#define _STL_H_

#include "siren.h"
#include "vec.h"
#include "shape.h"

#include <StlAPI.hxx>

#undef SIREN_STL_SAVE_USE_API

bool siren_stl_install(mrb_state* mrb, struct RClass* rclass);

#ifdef SIREN_STL_SAVE_USE_API
mrb_value siren_stl_save(mrb_state* mrb, mrb_value self);
#endif
mrb_value siren_stl_load(mrb_state* mrb, mrb_value self);

#endif
