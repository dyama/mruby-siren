/**
 * bsplinecurve.cpp
 */

#include "curve.h"

mrb_value siren_bsplinecurve_new(mrb_state* mrb, const opencascade::handle<Geom_Curve>* curve)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  mrb_value obj;
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "BSplineCurve")));
  void* p = mrb_malloc(mrb, sizeof(opencascade::handle<Geom_Curve>));
  opencascade::handle<Geom_Curve>* hgcurve = new(p) opencascade::handle<Geom_Curve>();
  *hgcurve = *curve;
  DATA_PTR(obj) = hgcurve;
  DATA_TYPE(obj) = &siren_bsplinecurve_type;
  return obj;
}

opencascade::handle<Geom_BSplineCurve> siren_bsplinecurve_get(mrb_state* mrb, mrb_value self)
{
  opencascade::handle<Geom_Curve> hgc
    = *static_cast<opencascade::handle<Geom_Curve>*>(mrb_get_datatype(mrb, self, &siren_bsplinecurve_type));
  if (hgc.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Curve."); }
  opencascade::handle<Geom_BSplineCurve> bsplinecurve = opencascade::handle<Geom_BSplineCurve>::DownCast(hgc);
  if (bsplinecurve.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not BSplineCurve."); }
  return bsplinecurve;
}

bool siren_bsplinecurve_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_curve = siren_curve_rclass(mrb);
  struct RClass* cls_bsplinecurve = mrb_define_class_under(mrb, mod_siren, "BSplineCurve", cls_curve);
  MRB_SET_INSTANCE_TT(cls_bsplinecurve, MRB_TT_DATA);
  mrb_define_method(mrb, cls_bsplinecurve, "initialize", siren_bsplinecurve_init,    MRB_ARGS_REQ(4) | MRB_ARGS_OPT(1));
  mrb_define_method(mrb, cls_bsplinecurve, "degree",     siren_bsplinecurve_degree,  MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_bsplinecurve, "knots",      siren_bsplinecurve_knots,   MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_bsplinecurve, "mults",      siren_bsplinecurve_mults,   MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_bsplinecurve, "poles",      siren_bsplinecurve_poles,   MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_bsplinecurve, "weights",    siren_bsplinecurve_weights, MRB_ARGS_NONE());
  return true;
}

mrb_value siren_bsplinecurve_init(mrb_state* mrb, mrb_value self)
{
  mrb_int d;
  mrb_value ks, ms, ps, ws;
  int argc = mrb_get_args(mrb, "iAAA|A", &d, &ks, &ms, &ps, &ws);

  int plen = mrb_ary_len(mrb, ps);

  TColgp_Array1OfPnt poles(0, plen - 1);
  TColStd_Array1OfReal weights(0, plen - 1);
  for (int i=0; i < plen; i++) {
    poles.SetValue(i, siren_ary_to_pnt(mrb, mrb_ary_ref(mrb, ps, i)));
    if (argc >= 5) {
      mrb_value w = mrb_ary_ref(mrb, ws, i);
      weights.SetValue(i, mrb_float(w));
    }
    else {
      weights.SetValue(i, 1.0);
    }
  }

  int klen = mrb_ary_len(mrb, ks);
  TColStd_Array1OfReal knots(0, klen - 1);
  TColStd_Array1OfInteger mults(0, klen - 1);

  for (int i=0; i < klen; i++) {
    mrb_value knot = mrb_ary_ref(mrb, ks, i);
    knots.SetValue(i, mrb_float(knot));
    mrb_value mult = mrb_ary_ref(mrb, ms, i);
    mults.SetValue(i, (Standard_Integer)mrb_fixnum(mult));
  }

  opencascade::handle<Geom_Curve> curve
    = new Geom_BSplineCurve(poles, weights, knots, mults, d, Standard_False);

  // initialize において self は既に mrb_instance_alloc されているので、
  // DATA_PTR と DATA_TYPE のみを設定する
  void* p = mrb_malloc(mrb, sizeof(opencascade::handle<Geom_Curve>));
  opencascade::handle<Geom_Curve>* hgcurve = new(p) opencascade::handle<Geom_Curve>();
  *hgcurve = curve;
  DATA_PTR(self) = hgcurve;
  DATA_TYPE(self) = &siren_bsplinecurve_type;
  return self;
}

mrb_value siren_bsplinecurve_degree(mrb_state* mrb, mrb_value self)
{
  opencascade::handle<Geom_BSplineCurve> curve = siren_bsplinecurve_get(mrb, self);
  return mrb_fixnum_value((int)curve->Degree());
}

mrb_value siren_bsplinecurve_knots(mrb_state* mrb, mrb_value self)
{
  opencascade::handle<Geom_BSplineCurve> curve = siren_bsplinecurve_get(mrb, self);
  mrb_value knots = mrb_ary_new(mrb);
  for (int i = 1; i <= curve->NbKnots(); i++) {
    mrb_ary_push(mrb, knots, mrb_float_value(mrb, curve->Knot(i)));
  }
  return knots;
}

mrb_value siren_bsplinecurve_mults(mrb_state* mrb, mrb_value self)
{
  opencascade::handle<Geom_BSplineCurve> curve = siren_bsplinecurve_get(mrb, self);
  mrb_value mults = mrb_ary_new(mrb);
  for (int i = 1; i <= curve->NbKnots(); i++) {
    mrb_ary_push(mrb, mults, mrb_fixnum_value(curve->Multiplicity(i)));
  }
  return mults;
}

mrb_value siren_bsplinecurve_poles(mrb_state* mrb, mrb_value self)
{
  opencascade::handle<Geom_BSplineCurve> curve = siren_bsplinecurve_get(mrb, self);
  mrb_value poles = mrb_ary_new(mrb);
  for (int i = 1; i <= curve->NbPoles(); i++) {
    mrb_value item = mrb_ary_new(mrb);
    mrb_ary_push(mrb, item, mrb_float_value(mrb, curve->Pole(i).X()));
    mrb_ary_push(mrb, item, mrb_float_value(mrb, curve->Pole(i).Y()));
    mrb_ary_push(mrb, item, mrb_float_value(mrb, curve->Pole(i).Z()));
    mrb_ary_push(mrb, poles, item);
  }
  return poles;
}

mrb_value siren_bsplinecurve_weights(mrb_state* mrb, mrb_value self)
{
  opencascade::handle<Geom_BSplineCurve> curve = siren_bsplinecurve_get(mrb, self);
  mrb_value weights = mrb_ary_new(mrb);
  for (int i = 1; i <= curve->NbPoles(); i++) {
    mrb_ary_push(mrb, weights, mrb_float_value(mrb, curve->Weight(i)));
  }
  return weights;
}

