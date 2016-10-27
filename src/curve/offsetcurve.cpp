/**
 * offsetcurve.cpp
 * Implementation of singleton methods for OFFSETCURVE
 */

#include "curve.h"

mrb_value siren_offsetcurve_new(mrb_state* mrb, const opencascade::handle<Geom_Curve>* curve)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  mrb_value obj;
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "OffsetCurve")));
  void* p = mrb_malloc(mrb, sizeof(opencascade::handle<Geom_Curve>));
  opencascade::handle<Geom_Curve>* hgcurve = new(p) opencascade::handle<Geom_Curve>();
  *hgcurve = *curve;
  DATA_PTR(obj) = hgcurve;
  DATA_TYPE(obj) = &siren_offsetcurve_type;
  return obj;
}

opencascade::handle<Geom_OffsetCurve> siren_offsetcurve_get(mrb_state* mrb, mrb_value self)
{
  opencascade::handle<Geom_Curve> hgc = *static_cast<opencascade::handle<Geom_Curve>*>(mrb_get_datatype(mrb, self, &siren_offsetcurve_type));
  if (hgc.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Curve."); }
  opencascade::handle<Geom_OffsetCurve> offsetcurve = opencascade::handle<Geom_OffsetCurve>::DownCast(hgc);
  if (offsetcurve.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not OffsetCurve."); }
  return offsetcurve;
}

bool siren_offsetcurve_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_curve = siren_curve_rclass(mrb);
  struct RClass* cls_offsetcurve = mrb_define_class_under(mrb, mod_siren, "offsetcurve", cls_curve);
  MRB_SET_INSTANCE_TT(cls_offsetcurve, MRB_TT_DATA);
  mrb_define_method(mrb, cls_offsetcurve, "initialize", siren_curve_init, MRB_ARGS_NONE());
  return true;
}
