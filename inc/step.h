#ifndef _STEP_H_
#define _STEP_H_

#include "siren.h"
#include "vec.h"
#include "shape.h"

#include <STEPControl_Controller.hxx>
#include <STEPControl_Reader.hxx>
#include <STEPControl_Writer.hxx>
#include <Interface_Static.hxx>

bool siren_step_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_step_save(mrb_state* mrb, mrb_value self);
mrb_value siren_step_load(mrb_state* mrb, mrb_value self);

#endif
