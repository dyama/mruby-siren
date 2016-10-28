#ifndef _SIREN_H_
#define _SIREN_H_

// Configuration
#define SIREN_ENABLE_GPROP
#define SIREN_ENABLE_BO
#define SIREN_ENABLE_OFFSET
#define SIREN_ENABLE_SHHEALING
#define SIREN_ENABLE_STL
#define SIREN_ENABLE_IGES
#define SIREN_ENABLE_STEP

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
#include "mruby/variable.h"

// OpenCASCADE libraries
#include <Standard.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_Macro.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>

#include <gp_Pnt.hxx>

#include "common.h"

#endif
