#ifndef _SHAPE_SHELL_H_
#define _SHAPE_SHELL_H_

#include "siren.h"

#include <TopoDS.hxx>
#include <TopoDS_Shell.hxx>

static struct mrb_data_type siren_shell_type = { "Shell", siren_shape_final };
bool siren_shell_install(mrb_state* mrb, struct RClass* mod_siren);
TopoDS_Shell siren_shell_get(mrb_state* mrb, mrb_value self);
mrb_value siren_shell_new(mrb_state* mrb, const TopoDS_Shape* src);

#endif
