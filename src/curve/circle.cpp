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
  mrb_define_singleton_method(mrb, o, "radius",   siren_circle_radius,     MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "radius=",  siren_circle_radius_set, MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, o, "center",   siren_circle_center,     MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "center=",  siren_circle_center_set, MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, o, "area",     siren_circle_area,       MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "length",   siren_circle_length,     MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "normal",   siren_circle_normal,     MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "normal=",  siren_circle_normal_set, MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, o, "dir",      siren_circle_dir,        MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "dir=",     siren_circle_dir_set,    MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, o, "dist",     siren_circle_dist,       MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, o, "distdist", siren_circle_distdist,   MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, o, "contain",  siren_circle_contain,    MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
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

mrb_value siren_circle_area(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Circle) circle = siren_circle_get(mrb, self);
  return mrb_float_value(mrb, circle->Circ().Area());
}

mrb_value siren_circle_length(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Circle) circle = siren_circle_get(mrb, self);
  return mrb_float_value(mrb, circle->Circ().Length());
}

mrb_value siren_circle_normal(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Circle) circle = siren_circle_get(mrb, self);
  // Returns the main axis of the circle.
  // It is the axis perpendicular to the plane of the circle,
  // passing through the "Location" point (center) of the circle.
  gp_Ax1 axis = circle->Circ().Axis();
  return siren_dir_to_ary(mrb, axis.Direction());
}

mrb_value siren_circle_normal_set(mrb_state* mrb, mrb_value self)
{
  mrb_value norm;
  int argc = mrb_get_args(mrb, "A", &norm);
  gp_Dir dir = siren_ary_to_dir(mrb, norm);
  Handle(Geom_Circle) circle = siren_circle_get(mrb, self);
  gp_Circ circ = circle->Circ();
  gp_Ax1 axis = circ.Axis();
  axis.SetDirection(dir);
  circ.SetAxis(axis);
  circle->SetCirc(circ);
  return norm;
}

mrb_value siren_circle_dir(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Circle) circle = siren_circle_get(mrb, self);
  gp_Ax1 axis = circle->Circ().XAxis();
  return siren_dir_to_ary(mrb, axis.Direction());
}

mrb_value siren_circle_dir_set(mrb_state* mrb, mrb_value self)
{
  mrb_value val;
  int argc = mrb_get_args(mrb, "A", &val);
  gp_Dir dir = siren_ary_to_dir(mrb, val);
  Handle(Geom_Circle) circle = siren_circle_get(mrb, self);
  gp_Circ circ = circle->Circ();
  gp_Ax2 axis;
  axis.SetAxis(circ.Axis());
  axis.SetXDirection(dir);
  circ.SetPosition(axis);
  circle->SetCirc(circ);
  return val;
}

mrb_value siren_circle_dist(mrb_state* mrb, mrb_value self)
{
  mrb_value pos;
  int argc = mrb_get_args(mrb, "A", &pos);
  gp_Pnt p = siren_ary_to_pnt(mrb, pos);
  Handle(Geom_Circle) circle = siren_circle_get(mrb, self);
  gp_Circ circ = circle->Circ();
  return mrb_float_value(mrb, circ.Distance(p));
}

mrb_value siren_circle_distdist(mrb_state* mrb, mrb_value self)
{
  mrb_value pos;
  int argc = mrb_get_args(mrb, "A", &pos);
  gp_Pnt p = siren_ary_to_pnt(mrb, pos);
  Handle(Geom_Circle) circle = siren_circle_get(mrb, self);
  gp_Circ circ = circle->Circ();
  return mrb_float_value(mrb, circ.SquareDistance(p));
}

mrb_value siren_circle_contain(mrb_state* mrb, mrb_value self)
{
  mrb_value pos;
  mrb_float lintol = 1.0e-7;
  int argc = mrb_get_args(mrb, "A|f", &pos, &lintol);
  gp_Pnt p = siren_ary_to_pnt(mrb, pos);
  Handle(Geom_Circle) circle = siren_circle_get(mrb, self);
  gp_Circ circ = circle->Circ();
  return circ.Contains(p, lintol) ? mrb_true_value() : mrb_false_value();
}
