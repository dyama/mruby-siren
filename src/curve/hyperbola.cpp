/**
 * hyperbola.cpp
 * Implementation of singleton methods for HYPERBOLA
 */

#include "curve.h"

mrb_value siren_hyperbola_new(mrb_state* mrb, const Handle(Geom_Curve)* curve)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  mrb_value obj;
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Hyperbola")));
  void* p = mrb_malloc(mrb, sizeof(Handle(Geom_Curve)));
  Handle(Geom_Curve)* hgcurve = new(p) Handle(Geom_Curve)();
  *hgcurve = *curve;
  DATA_PTR(obj) = hgcurve;
  DATA_TYPE(obj) = &siren_hyperbola_type;
  return obj;
}

Handle(Geom_Hyperbola) siren_hyperbola_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *static_cast<Handle(Geom_Curve)*>(mrb_get_datatype(mrb, self, &siren_hyperbola_type));
  if (hgc.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Curve."); }
  Handle(Geom_Hyperbola) hyperbola = Handle(Geom_Hyperbola)::DownCast(hgc);
  if (hyperbola.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Hyperbola."); }
  return hyperbola;
}

bool siren_hyperbola_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_curve = siren_curve_rclass(mrb);
  struct RClass* cls_hyperbola = mrb_define_class_under(mrb, mod_siren, "Hyperbola", cls_curve);
  MRB_SET_INSTANCE_TT(cls_hyperbola, MRB_TT_DATA);
  mrb_define_method(mrb, cls_hyperbola, "initialize", siren_curve_init, MRB_ARGS_NONE());
  return true;
}
