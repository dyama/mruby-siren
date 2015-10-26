#include "gprop.h"

mrb_value siren_gprop_volume(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  GProp_GProps gprops;
  BRepGProp::VolumeProperties(*shape, gprops);
  Standard_Real vol = gprops.Mass();
  return mrb_float_value(mrb, (mrb_float)vol);
}

mrb_value siren_gprop_cog(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  GProp_GProps gprops;
  BRepGProp::VolumeProperties(*shape, gprops);
  gp_Pnt cog = gprops.CentreOfMass();
  return siren_pnt_to_ary(mrb, cog);
}

mrb_value siren_gprop_area(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  GProp_GProps gprops;
  BRepGProp::SurfaceProperties(*shape, gprops);
  Standard_Real area = gprops.Mass();
  return mrb_float_value(mrb, area);
}

