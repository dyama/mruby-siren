#ifndef _SKIN_H_
#define _SKIN_H_

#include "siren.h"
#include "shape.h"

#include <AIS_Shape.hxx>

void siren_skin_final(mrb_state* mrb, void* p);
bool siren_skin_install(mrb_state* mrb, struct RClass* rclass);
static struct mrb_data_type siren_skin_type = { "Skin", siren_skin_final };
//Handle(AIS_Shape) siren_skin_get(mrb_state* mrb, mrb_value obj);
AIS_Shape* siren_skin_get(mrb_state* mrb, mrb_value obj);

//mrb_value siren_skin_new(mrb_state* mrb, const TopoDS_skin& skin);

mrb_value siren_skin_init(mrb_state* mrb, mrb_value self);

mrb_value siren_skin_color_set(mrb_state* mrb, mrb_value self);
mrb_value siren_skin_material_set(mrb_state* mrb, mrb_value self);
mrb_value siren_skin_transparency_set(mrb_state* mrb, mrb_value self);

#endif
