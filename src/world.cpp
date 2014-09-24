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
  void* p_viewer = mrb_malloc(mrb, sizeof(V3d_Viewer));
  TCollection_ExtendedString a3DName("siren3d"); // Viewer name
  Standard_CString aDomain = "";                 // Domain name
  wa->viewer = new(p_viewer) V3d_Viewer(
      wa->driver,
      a3DName.ToExtString(),
      aDomain,
      1000.0,
      V3d_XposYnegZpos,
      Quantity_NOC_BLACK
      );

  // init context
  void* p_context = mrb_malloc(mrb, sizeof(AIS_InteractiveContext));
  wa->context = new(p_context) AIS_InteractiveContext(wa->viewer);

  DATA_PTR(self) = wa;
  DATA_TYPE(self) = &siren_world_type;

  return self;
}

void siren_world_final(mrb_state* mrb, void* p)
{
  struct world_attr* wa = static_cast<struct world_attr*>(p);
  // driver is not managed under mruby GC
  mrb_free(mrb, wa->viewer);
  mrb_free(mrb, wa->context);
  mrb_free(mrb, wa);
}

