#ifndef _IGES_H_
#define _IGES_H_
#ifdef SIREN_ENABLE_IGES

#include "siren.h"
#include "vec.h"
#include "shape.h"

#include <IGESControl_Controller.hxx>
#include <IGESControl_Reader.hxx>
#include <IGESControl_Writer.hxx>
#include <Interface_Static.hxx>
//#include <IFSelect_ReturnStatus.hxx>

bool siren_iges_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_iges_save(mrb_state* mrb, mrb_value self);
mrb_value siren_iges_load(mrb_state* mrb, mrb_value self);

#endif
#endif
