/**
 * ellipse.cpp
 * Implementation of singleton methods for ELLIPSE
 */

#include "curve.h"

mrb_value siren_ellipse_new(mrb_state* mrb, const handle<Geom_Curve>* curve)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  mrb_value obj;
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Ellipse")));
  void* p = mrb_malloc(mrb, sizeof(handle<Geom_Curve>));
  handle<Geom_Curve>* hgcurve = new(p) handle<Geom_Curve>();
  *hgcurve = *curve;
  DATA_PTR(obj) = hgcurve;
  DATA_TYPE(obj) = &siren_ellipse_type;
  return obj;
}

handle<Geom_Ellipse> siren_ellipse_get(mrb_state* mrb, mrb_value self)
{
  handle<Geom_Curve> hgc = *static_cast<handle<Geom_Curve>*>(mrb_get_datatype(mrb, self, &siren_ellipse_type));
  if (hgc.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Curve."); }
  handle<Geom_Ellipse> ellipse = handle<Geom_Ellipse>::DownCast(hgc);
  if (ellipse.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Ellipse."); }
  return ellipse;
}

bool siren_ellipse_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_curve = siren_curve_rclass(mrb);
  struct RClass* cls_ellipse = mrb_define_class_under(mrb, mod_siren, "Ellipse", cls_curve);
  MRB_SET_INSTANCE_TT(cls_ellipse, MRB_TT_DATA);
  mrb_define_method(mrb, cls_ellipse, "initialize", siren_curve_init, MRB_ARGS_NONE());
  return true;
}
