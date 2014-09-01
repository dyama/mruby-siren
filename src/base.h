#ifndef _BASE_H_
#define _BASE_H_

#include "siren.h"
#include "shape.h"
#include "exp.h"

#include <BRepAdaptor_Curve.hxx>
#include <GCPnts_UniformDeflection.hxx>

bool siren_base_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_base_edge2pts(mrb_state* mrb, mrb_value self);

#endif
