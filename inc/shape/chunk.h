#ifndef _SHAPE_CHUNK_H_
#define _SHAPE_CHUNK_H_

#ifdef SIREN_ENABLE_CHUNK

#include "siren.h"

#include <TopoDS.hxx>
#include <TopoDS_CompSolid.hxx>

static struct mrb_data_type siren_chunk_type = { "Chunk", siren_shape_final };
bool siren_chunk_install(mrb_state* mrb, struct RClass* mod_siren);
TopoDS_CompSolid siren_chunk_get(mrb_state* mrb, mrb_value self);
mrb_value siren_chunk_new(mrb_state* mrb, const TopoDS_Shape* src);
mrb_value siren_chunk_obj(mrb_state* mrb);
struct RClass* siren_chunk_rclass(mrb_state* mrb);

mrb_value siren_chunk_init(mrb_state* mrb, mrb_value self);
mrb_value siren_chunk_to_solid(mrb_state* mrb, mrb_value self);

#endif

#endif
