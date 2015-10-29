#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "siren.h"
#include "vec.h"
#include "bndbox.h"
#include "trans.h"

#ifdef SIREN_ENABLE_GPROP
#include "gprop.h"
#endif

#ifdef SIREN_ENABLE_BOOL
#include "bool.h"
#endif

#include "singleton_edge.h"
#include "singleton_face.h"
#include "wire.h"

#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>

#include <TopExp_Explorer.hxx>

#include <BRepAlgoAPI_Section.hxx>

void siren_shape_final(mrb_state* mrb, void* p);
bool siren_shape_install(mrb_state* mrb, struct RClass* rclass);
static struct mrb_data_type siren_shape_type = { "Shape", siren_shape_final };
TopoDS_Shape* siren_shape_get(mrb_state* mrb, mrb_value obj);

mrb_value siren_shape_new(mrb_state* mrb, const TopoDS_Shape& shape);

mrb_value siren_shape_init(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_to_s(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_is_null(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_shapetype(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_pos(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_trans(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_set_trans(mrb_state* mrb, mrb_value self);

mrb_value siren_shape_bndbox(mrb_state* mrb, mrb_value self);

mrb_value siren_shape_translate_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_rotate_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_scale_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_mirror_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_move_bang(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_translate(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_rotate(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_scale(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_mirror(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_move(mrb_state* mrb, mrb_value self);

mrb_value siren_shape_hashcode(mrb_state* mrb, mrb_value self);

mrb_value siren_shape_is_partner(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_is_same(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_is_equal(mrb_state* mrb, mrb_value self);

mrb_value siren_shape_explore(mrb_state* mrb, mrb_value self);

mrb_value siren_shape_section(mrb_state* mrb, mrb_value self);

mrb_value siren_shape_reverse(mrb_state* mrb, mrb_value self);
mrb_value siren_shape_reverse_bang(mrb_state* mrb, mrb_value self);

#endif
