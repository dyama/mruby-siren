#ifndef _GPROP_H_
#define _GPROP_H_

#include "siren.h"
#include "shape.h"

#include <GProp_GProps.hxx>
#include <BRepGProp.hxx>

bool siren_gprop_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_gprop_volume(mrb_state* mrb, mrb_value self);
mrb_value siren_gprop_cog(mrb_state* mrb, mrb_value self);
mrb_value siren_gprop_area(mrb_state* mrb, mrb_value self);
// 面心位置

#endif
