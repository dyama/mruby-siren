#ifndef _SHAPE_SOLID_H_
#define _SHAPE_SOLID_H_

#include "siren.h"

#include <TopoDS.hxx>
#include <TopoDS_Solid.hxx>

static struct mrb_data_type siren_solid_type = { "Solid", siren_shape_final };
bool siren_solid_install(mrb_state* mrb, struct RClass* mod_siren);
TopoDS_Solid siren_solid_get(mrb_state* mrb, mrb_value self);
mrb_value siren_solid_new(mrb_state* mrb, const TopoDS_Shape* src);
mrb_value siren_solid_obj(mrb_state* mrb);

#endif
