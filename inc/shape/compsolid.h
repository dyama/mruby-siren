#ifndef _SHAPE_COMPSOLID_H_
#define _SHAPE_COMPSOLID_H_

#include "siren.h"

#include <TopoDS.hxx>
#include <TopoDS_CompSolid.hxx>

void siren_compsolid_install(mrb_state* mrb, RObject* o);

#endif
