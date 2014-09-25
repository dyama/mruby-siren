#include "world.h"

struct world_attr* siren_world_attr_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<struct world_attr*>(mrb_get_datatype(mrb, obj, &siren_world_type));
}

bool siren_world_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "World", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", siren_world_init, ARGS_OPT(1));
  mrb_define_method(mrb, rclass, "add",        siren_world_add, ARGS_REQ(1));
  return true;
}

mrb_value siren_world_init(mrb_state* mrb, mrb_value self)
{
  mrb_value dispname;
  int argc = mrb_get_args(mrb, "|S", &dispname);

  void* p = mrb_malloc(mrb, sizeof(struct world_attr));
  struct world_attr* wa = new(p) struct world_attr;

  // init driver
  Handle(Aspect_DisplayConnection) dc;
    dc = argc ? new Aspect_DisplayConnection((Standard_CString)RSTRING_PTR(dispname)) : NULL;
  wa->driver = Graphic3d::InitGraphicDriver(dc);

  // init viewer
  TCollection_ExtendedString a3DName("siren3d"); // Viewer name
  Standard_CString aDomain = "";                 // Domain name
  wa->viewer = new V3d_Viewer(
      wa->driver,
      a3DName.ToExtString(),
      aDomain,
      1000.0,
      V3d_XposYnegZpos,
      Quantity_NOC_BLACK
      );

  // light setting
  wa->viewer->SetDefaultLights();
  wa->viewer->SetLightOn();

  // init context
  wa->context = new AIS_InteractiveContext(wa->viewer);
  wa->context->UpdateCurrentViewer();

  DATA_PTR(self) = wa;
  DATA_TYPE(self) = &siren_world_type;

  return self;
}

void siren_world_final(mrb_state* mrb, void* p)
{
  struct world_attr* wa = static_cast<struct world_attr*>(p);
  // driver is not managed under mruby GC
  //mrb_free(mrb, wa->viewer);
  //mrb_free(mrb, wa->context);
  mrb_free(mrb, wa);
}

mrb_value siren_world_add(mrb_state* mrb, mrb_value self)
{
  mrb_value skin;
  int argc = mrb_get_args(mrb, "o", &skin);

  struct world_attr* wa = siren_world_attr_get(mrb, self);

  Handle(AIS_Shape) hashape = siren_skin_get(mrb, skin);
  wa->context->SetDisplayMode(hashape, 1, Standard_False);
  wa->context->Display(hashape, 1);
  wa->context->Activate(hashape);
  //wa->context->UpdateCurrentViewer();

  return mrb_nil_value();
}
