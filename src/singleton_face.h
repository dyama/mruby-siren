#ifndef _SINGLETON_FACE_H_
#define _SINGLETON_FACE_H_

#include "siren.h"
#include "shape.h"
#include "vec.h"

#include <TopoDS_Face.hxx>
#include <BRepTools.hxx>
#include <GeomLProp_SLProps.hxx>

void siren_face_install(mrb_state* mrb, RObject* o);

mrb_value siren_face_normal(mrb_state* mrb, mrb_value self);

#endif
