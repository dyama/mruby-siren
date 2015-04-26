#include "camera.h"

#if !defined(_WIN32) && defined(SIREN_ENABLE_VIS)

Handle(V3d_View) siren_camera_get(mrb_state* mrb, mrb_value obj)
{
  void* p = mrb_get_datatype(mrb, obj, &siren_camera_type);
  return static_cast<const V3d_View* /* Handle(AIS_Shape) */>(p);
}

bool siren_camera_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Camera", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", siren_camera_init, MRB_ARGS_OPT(1));
  mrb_define_method(mrb, rclass, "fit", siren_camera_fit,         MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "fitz", siren_camera_fit,        MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "proj=", siren_camera_set_proj,  MRB_ARGS_REQ(1));

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
#if OCC_VERSION_MAJOR >= 6 && OCC_VERSION_MINOR == 7
  view = pers ?
    new V3d_PerspectiveView(wa->context->CurrentViewer())
    : wa->context->CurrentViewer()->CreateView();
#else
  view = wa->context->CurrentViewer()->CreateView();
#endif

#ifdef _WIN32
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
  view->TriedronDisplay(Aspect_TOTP_RIGHT_UPPER, Quantity_NOC_WHITE, 0.1, V3d_ZBUFFER);

  //view->SetAntialiasingOn();

  view->Redraw();

  DATA_PTR(self) = view;
  DATA_TYPE(self) = &siren_camera_type;

  return self;
}

void siren_camera_final(mrb_state* mrb, void* p)
{
  // struct camera_attr* wa = static_cast<struct camera_attr*>(p);
  // mrb_free(mrb, wa);
}

mrb_value siren_camera_fit(mrb_state* mrb, mrb_value self)
{
  Handle(V3d_View) view = siren_camera_get(mrb, self);
  view->FitAll();
  return mrb_nil_value();
}

mrb_value siren_camera_fitz(mrb_state* mrb, mrb_value self)
{
  Handle(V3d_View) view = siren_camera_get(mrb, self);
  view->ZFitAll();
  return mrb_nil_value();
}

mrb_value siren_camera_set_proj(mrb_state* mrb, mrb_value self)
{
  mrb_int dir;
  int argc = mrb_get_args(mrb, "i", &dir);
  Handle(V3d_View) view = siren_camera_get(mrb, self);
  view->SetProj((V3d_TypeOfOrientation)dir);
  return mrb_nil_value();
}

#endif
