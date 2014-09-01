#include "gprop.h"

bool siren_gprop_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "GProp");
  mrb_define_class_method(mrb, rclass, "volume", siren_gprop_volume, ARGS_REQ(1));
  mrb_define_class_method(mrb, rclass, "cog",    siren_gprop_cog,    ARGS_REQ(1));
  mrb_define_class_method(mrb, rclass, "area",   siren_gprop_area,   ARGS_REQ(1));
  return true;
}

mrb_value siren_gprop_volume(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  int argc = mrb_get_args(mrb, "o", &target);

  TopoDS_Shape* shape = siren_shape_get(mrb, target);

  GProp_GProps gprops;
  BRepGProp::VolumeProperties(*shape, gprops);
  Standard_Real vol = gprops.Mass();

  return mrb_float_value(mrb, (mrb_float)vol);
}

mrb_value siren_gprop_cog(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  int argc = mrb_get_args(mrb, "o", &target);

  TopoDS_Shape* shape = siren_shape_get(mrb, target);

  GProp_GProps gprops;
  BRepGProp::VolumeProperties(*shape, gprops);
  gp_Pnt cog = gprops.CentreOfMass();

  return siren_vec_new(mrb, cog.X(), cog.Y(), cog.Z());
}

mrb_value siren_gprop_area(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  int argc = mrb_get_args(mrb, "o", &target);

  TopoDS_Shape* shape = siren_shape_get(mrb, target);

  GProp_GProps System;
  BRepGProp::SurfaceProperties(*shape, System);
  Standard_Real Area = System.Mass();

  return mrb_float_value(mrb, Area);
}

