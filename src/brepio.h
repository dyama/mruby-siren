#ifndef _BREPIO_H_
#define _BREPIO_H_

#include "siren.h"
#include "vec.h"
#include "shape.h"

#include <BRepTools.hxx>
#include <BRep_Builder.hxx>

bool siren_brepio_install(mrb_state* mrb, struct RClass* rclass);

mrb_method(brepio_save);
mrb_method(brepio_load);

#endif
