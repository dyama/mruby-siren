#ifndef _SHAPE_COMPOUND_H_
#define _SHAPE_COMPOUND_H_

#include "siren.h"

#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>

static struct mrb_data_type siren_compound_type = { "Compound", siren_shape_final };
bool siren_compound_install(mrb_state* mrb, struct RClass* mod_siren);
TopoDS_Compound siren_compound_get(mrb_state* mrb, mrb_value self);
mrb_value siren_compound_new(mrb_state* mrb, const TopoDS_Shape* src);
mrb_value siren_compound_obj(mrb_state* mrb);
struct RClass* siren_compound_rclass(mrb_state* mrb);

mrb_value siren_compound_init(mrb_state* mrb, mrb_value self);

#endif
