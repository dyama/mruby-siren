#include "curve/circle.h"

mrb_value siren_circle_new(mrb_state* mrb, const Handle(Geom_Curve)* curve)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  mrb_value obj;
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Circle")));
  void* p = mrb_malloc(mrb, sizeof(Handle(Geom_Curve)));
  Handle(Geom_Curve)* hgcurve = new(p) Handle(Geom_Curve)();
  *hgcurve = *curve;
  DATA_PTR(obj) = hgcurve;
  DATA_TYPE(obj) = &siren_circle_type;
  return obj;
}

Handle(Geom_Circle) siren_circle_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *static_cast<Handle(Geom_Curve)*>(mrb_get_datatype(mrb, self, &siren_circle_type));
  if (hgc.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Curve."); }
  Handle(Geom_Circle) circle = Handle(Geom_Circle)::DownCast(hgc);
  if (circle.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Circle."); }
  return circle;
}

bool siren_circle_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_curve = siren_curve_rclass(mrb);
  struct RClass* cls_circle = mrb_define_class_under(mrb, mod_siren, "Circle", mrb->object_class);
  MRB_SET_INSTANCE_TT(cls_circle, MRB_TT_DATA);
  mrb_define_method(mrb, cls_circle, "initialize", siren_curve_init, MRB_ARGS_NONE());

  mrb_define_method(mrb, cls_circle, "radius",   siren_circle_radius,     MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_circle, "radius=",  siren_circle_radius_set, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_circle, "center",   siren_circle_center,     MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_circle, "center=",  siren_circle_center_set, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_circle, "area",     siren_circle_area,       MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_circle, "length",   siren_circle_length,     MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_circle, "normal",   siren_circle_normal,     MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_circle, "normal=",  siren_circle_normal_set, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_circle, "dir",      siren_circle_dir,        MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_circle, "dir=",     siren_circle_dir_set,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_circle, "dist",     siren_circle_dist,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_circle, "distdist", siren_circle_distdist,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_circle, "contain",  siren_circle_contain,    MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  return true;
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
