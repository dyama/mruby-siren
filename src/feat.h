#ifndef _FEAT_H_
#define _FEAT_H_

#include "siren.h"
#include "shape.h"

#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <BRepFeat_SplitShape.hxx>

bool siren_feat_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_feat_splitFxW(mrb_state* mrb, mrb_value self);

#endif
