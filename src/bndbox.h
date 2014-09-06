#ifndef _BNDBOX_H_
#define _BNDBOX_H_

#include "siren.h"
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>

bool siren_bndbox_install(mrb_state* mrb, struct RClass* rclass);
void siren_bndbox_final(mrb_state* mrb, void* p);
static struct mrb_data_type siren_bndbox_type = { "BndBox", siren_bndbox_final };

mrb_value siren_bndbox_new(mrb_state* mrb, const TopoDS_Shape& shape);
Bnd_Box* siren_bndbox_get(mrb_state* mrb, mrb_value obj);

mrb_value siren_bndbox_init(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_min(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_max(mrb_state* mrb, mrb_value self);

#endif
