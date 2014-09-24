#include "camera.h"

bool siren_camera_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Camera", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", siren_camera_init, ARGS_OPT(1));

  return true;
}

mrb_value siren_camera_init(mrb_state* mrb, mrb_value self)
{
  mrb_value world;
  mrb_int whd;
  int argc = mrb_get_args(mrb, "oi", &world, &whd);

  world_attr* wa = siren_world_attr_get(mrb, world);

  bool pers = false;
  // How can I manage Handle(...) object with mruby GC in this case?
  Handle(V3d_View) view;
  view = pers ?
    new V3d_PerspectiveView(wa->context->CurrentViewer())
    : wa->context->CurrentViewer()->CreateView();

#if _WNT
  Handle(WNT_Window) window = new WNT_Window((Aspect_Handle)whd);
#else
  Handle(Xw_Window) window = new Xw_Window(wa->driver->GetDisplayConnection(), *((Window*)whd));
#endif
  view->SetWindow(window);
  if (!window->IsMapped()) {
    window->Map();
  }

  Quantity_Color color_top(0.20, 0.20, 0.20, Quantity_TOC_RGB);
  Quantity_Color color_btm(0.30, 0.45, 0.60, Quantity_TOC_RGB);
  view->SetBgGradientColors(color_top, color_btm, Aspect_GFM_VER, Standard_False);

  // Show trihedron at right upper of view.
  // view->TriedronDisplay(Aspect_TOPP_RIGHT_UPPER, Quantity_NOC_WHITE, 0.1, V3d_ZBUFFER);

  DATA_PTR(self) = view;
  DATA_TYPE(self) = &siren_camera_type;

  return self;
}

void siren_camera_final(mrb_state* mrb, void* p)
{
  // struct camera_attr* wa = static_cast<struct camera_attr*>(p);
  // mrb_free(mrb, wa);
}

