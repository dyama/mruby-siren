#ifndef _WORLD_H_
#define _WORLD_H_

#include "siren.h"

#include <Graphic3d_GraphicDriver.hxx>
#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>

#include <Graphic3d.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <TCollection_ExtendedString.hxx>
#include <Standard_PrimitiveTypes.hxx>

struct world_attr
{
  Handle(Graphic3d_GraphicDriver) driver;
  Handle(AIS_InteractiveContext)  context;
  Handle(V3d_Viewer)              viewer;
};

void siren_world_final(mrb_state* mrb, void* p);
bool siren_world_install(mrb_state* mrb, struct RClass* rclass);
static struct mrb_data_type siren_world_type = { "World", siren_world_final };
struct world_attr* siren_world_attr_get(mrb_state* mrb, mrb_value obj);

mrb_value siren_world_init(mrb_state* mrb, mrb_value self);

#endif
