#include "curve/circle.h"

Handle(Geom_Circle) siren_circle_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_Circle) circle = Handle(Geom_Circle)::DownCast(hgc);
  if (circle.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not circle.");
  }
  return circle;
}

void siren_circle_install(mrb_state* mrb, RObject* o)
{
  mrb_define_singleton_method(mrb, o, "radius",  siren_circle_radius, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "radius=", siren_circle_radius_set, MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, o, "center",  siren_circle_center, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "center=", siren_circle_center_set, MRB_ARGS_REQ(1));
  return;
}

mrb_value siren_circle_radius(mrb_state* mrb, mrb_value self)
{
  Standard_Real r = siren_circle_get(mrb, self)->Radius();
  return mrb_float_value(mrb, r);
}

mrb_value siren_circle_radius_set(mrb_state* mrb, mrb_value self)
{
  mrb_float r;
  int argc = mrb_get_args(mrb, "f", &r);
  siren_circle_get(mrb, self)->SetRadius(r);
  return mrb_nil_value();
}

mrb_value siren_circle_center(mrb_state* mrb, mrb_value self)
{
  gp_Pnt center = siren_circle_get(mrb, self)->Circ().Location();
  return siren_pnt_to_ary(mrb, center);
}

mrb_value siren_circle_center_set(mrb_state* mrb, mrb_value self)
{
  mrb_value pos;
  int argc = mrb_get_args(mrb, "A", &pos);
  gp_Pnt p = siren_ary_to_pnt(mrb, pos);
  Handle(Geom_Circle) circle = siren_circle_get(mrb, self);
  gp_Circ circ = circle->Circ();
  circ.SetLocation(p);
  circle->SetCirc(circ);
  return pos;
}

