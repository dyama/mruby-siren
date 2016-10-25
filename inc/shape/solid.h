#ifndef _SHAPE_SOLID_H_
#define _SHAPE_SOLID_H_

#include "siren.h"

#include <TopoDS.hxx>
#include <TopoDS_Solid.hxx>

void siren_solid_install(mrb_state* mrb, RObject* o);

#endif
