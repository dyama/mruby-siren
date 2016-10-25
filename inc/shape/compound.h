#ifndef _SHAPE_COMPOUND_H_
#define _SHAPE_COMPOUND_H_

#include "siren.h"

#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>

void siren_compound_install(mrb_state* mrb, RObject* o);

#endif
