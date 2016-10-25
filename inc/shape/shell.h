#ifndef _SHAPE_SHELL_H_
#define _SHAPE_SHELL_H_

#include "siren.h"

#include <TopoDS.hxx>
#include <TopoDS_Shell.hxx>

void siren_shell_install(mrb_state* mrb, RObject* o);

#endif
