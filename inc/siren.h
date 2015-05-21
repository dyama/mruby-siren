#ifndef _SIREN_H_
#define _SIREN_H_

// Configuration
#define SIREN_ENABLE_VIS
#define SIREN_ENABLE_GPROP
#define SIREN_ENABLE_BOOL
#define SIREN_ENABLE_STL

// C++ libraries
#include <iostream>
#include <stdlib.h>

// placement new
#include <new>

// mruby libraries
#include "mruby.h"
#include "mruby/array.h"
#include "mruby/data.h"
#include "mruby/string.h"
#include "mruby/class.h"

// OpenCASCADE libraries
#include <config.h>
#include <Standard.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_Macro.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>

#include <gp_Pnt.hxx>

#include "common.h"

// Dummy method
inline mrb_value mrb_method_dummy(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

#endif
