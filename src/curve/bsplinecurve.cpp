/**
 * bsplinecurve.cpp
 * Implementation of singleton methods for BSPLINECURVE
 */

#include "curve.h"

mrb_value siren_bsplinecurve_new(mrb_state* mrb, const Handle(Geom_Curve)* curve)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  mrb_value obj;
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "BSplineCurve")));
  void* p = mrb_malloc(mrb, sizeof(Handle(Geom_Curve)));
  Handle(Geom_Curve)* hgcurve = new(p) Handle(Geom_Curve)();
  *hgcurve = *curve;
  DATA_PTR(obj) = hgcurve;
  DATA_TYPE(obj) = &siren_bsplinecurve_type;
  return obj;
}

Handle(Geom_BSplineCurve) siren_bsplinecurve_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *static_cast<Handle(Geom_Curve)*>(mrb_get_datatype(mrb, self, &siren_bsplinecurve_type));
  if (hgc.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Curve."); }
  Handle(Geom_BSplineCurve) bsplinecurve = Handle(Geom_BSplineCurve)::DownCast(hgc);
  if (bsplinecurve.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not BSplineCurve."); }
  return bsplinecurve;
}

bool siren_bsplinecurve_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_curve = siren_curve_rclass(mrb);
  struct RClass* cls_bsplinecurve = mrb_define_class_under(mrb, mod_siren, "BSplineCurve", cls_curve);
  MRB_SET_INSTANCE_TT(cls_bsplinecurve, MRB_TT_DATA);
  mrb_define_method(mrb, cls_bsplinecurve, "initialize", siren_curve_init, MRB_ARGS_NONE());
  return true;
}
