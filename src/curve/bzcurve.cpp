/**
 * bzcurve.cpp
 */

#include "curve.h"

mrb_value siren_bzcurve_new(mrb_state* mrb, const opencascade::handle<Geom_Curve>* curve)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  mrb_value obj;
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "BzCurve")));
  void* p = mrb_malloc(mrb, sizeof(opencascade::handle<Geom_Curve>));
  opencascade::handle<Geom_Curve>* hgcurve = new(p) opencascade::handle<Geom_Curve>();
  *hgcurve = *curve;
  DATA_PTR(obj) = hgcurve;
  DATA_TYPE(obj) = &siren_bzcurve_type;
  return obj;
}

opencascade::handle<Geom_BezierCurve> siren_bzcurve_get(mrb_state* mrb, mrb_value self)
{
  opencascade::handle<Geom_Curve> hgc = *static_cast<opencascade::handle<Geom_Curve>*>(mrb_get_datatype(mrb, self, &siren_bzcurve_type));
  if (hgc.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Curve."); }
  opencascade::handle<Geom_BezierCurve> bzcurve = opencascade::handle<Geom_BezierCurve>::DownCast(hgc);
  if (bzcurve.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not BzCurve."); }
  return bzcurve;
}

bool siren_bzcurve_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_curve = siren_curve_rclass(mrb);
  struct RClass* cls_bzcurve = mrb_define_class_under(mrb, mod_siren, "BzCurve", cls_curve);
  MRB_SET_INSTANCE_TT(cls_bzcurve, MRB_TT_DATA);
  mrb_define_method(mrb, cls_bzcurve, "initialize", siren_bzcurve_init,   MRB_ARGS_NONE());
  // mrb_define_method(mrb, cls_bzcurve, "degree",     siren_bzcurve_degree, MRB_ARGS_NONE());
  return true;
}

mrb_value siren_bzcurve_init(mrb_state* mrb, mrb_value self)
{
  mrb_value ps, ws;
  int argc = mrb_get_args(mrb, "A|A", &ps, &ws);
  bool has_weight = argc == 2;
  int plen = mrb_ary_len(mrb, ps);
  TColgp_Array1OfPnt poles(1, plen);
  TColStd_Array1OfReal weights(1, plen);
  // Start index of weights must be 1. Crash construction of Geom_BezierCurve
  // if another index specified.
  for (int i = 0; i < plen; i++) {
    poles.SetValue(i + 1, siren_ary_to_pnt(mrb, mrb_ary_ref(mrb, ps, i)));
    if (has_weight) {
      mrb_value w = mrb_ary_ref(mrb, ws, i);
      weights.SetValue(i + 1, mrb_float(w));
    }
  }
  opencascade::handle<Geom_Curve> curve = nullptr;
  try {
    if (has_weight) {
      curve = new Geom_BezierCurve(poles, weights);
    }
    else {
      curve = new Geom_BezierCurve(poles);
    }
  }
  catch (...) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a BzCurve.");
  }
  void* p = mrb_malloc(mrb, sizeof(opencascade::handle<Geom_Curve>));
  opencascade::handle<Geom_Curve>* hgcurve = new(p) opencascade::handle<Geom_Curve>();
  *hgcurve = curve;
  DATA_PTR(self) = hgcurve;
  DATA_TYPE(self) = &siren_bzcurve_type;
  return self;
}

