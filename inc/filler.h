#ifndef _FILLER_H_
#define _FILLER_H_

#include "siren.h"

#include <BRepFill_Filling.hxx>

bool siren_filler_install(mrb_state* mrb, struct RClass* rclass);
void siren_filler_final(mrb_state* mrb, void* p);
static struct mrb_data_type siren_filler_type = { "Filler", siren_filler_final };

BRepFill_Filling* siren_filler_get(mrb_state* mrb, mrb_value obj);

mrb_value siren_filler_init(mrb_state* mrb, mrb_value self);
mrb_value siren_filler_add_bound(mrb_state* mrb, mrb_value self);
mrb_value siren_filler_add(mrb_state* mrb, mrb_value self);
mrb_value siren_filler_build(mrb_state* mrb, mrb_value self);
mrb_value siren_filler_is_done(mrb_state* mrb, mrb_value self);
mrb_value siren_filler_face(mrb_state* mrb, mrb_value self);
mrb_value siren_filler_g0error(mrb_state* mrb, mrb_value self);
mrb_value siren_filler_g1error(mrb_state* mrb, mrb_value self);
mrb_value siren_filler_g2error(mrb_state* mrb, mrb_value self);

#endif
