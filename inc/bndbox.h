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
struct RClass* siren_bndbox_rclass(mrb_state* mrb);
#define siren_is_bndbox(obj) (DATA_TYPE(obj) == &siren_bndbox_type)

mrb_value siren_bndbox_init(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_to_s(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_min(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_max(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_add(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_is_out(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_center(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_xsize(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_ysize(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_zsize(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_is_void(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_is_whole(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_void_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_whole_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_is_xthin(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_is_ythin(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_is_zthin(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_is_openxmin(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_is_openxmax(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_is_openymin(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_is_openymax(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_is_openzmin(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_is_openzmax(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_openxmin_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_openxmax_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_openymin_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_openymax_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_openzmin_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_openzmax_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_set_gap(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_get_gap(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_dist(mrb_state* mrb, mrb_value self);
mrb_value siren_bndbox_square(mrb_state* mrb, mrb_value self);

#endif
