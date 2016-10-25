#include "curve/circle.h"

void siren_circle_install(mrb_state* mrb, RObject* o)
{
  mrb_define_singleton_method(mrb, o, "radius",  siren_circle_radius, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "radius=", siren_circle_radius_set, MRB_ARGS_REQ(1));
  return;
}

mrb_value siren_circle_radius(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_Circle) circle = Handle(Geom_Circle)::DownCast(hgc);
  if (circle.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not circle.");
  }
  Standard_Real r = circle->Radius();
  return mrb_float_value(mrb, r);
}

mrb_value siren_circle_radius_set(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_Circle) circle = Handle(Geom_Circle)::DownCast(hgc);
  if (circle.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not circle.");
  }
  mrb_float r;
  int argc = mrb_get_args(mrb, "f", &r);
  circle->SetRadius(r);
  return mrb_nil_value();
}
