/**
 * parabola.cpp
 * Implementation of singleton methods for PARABOLA
 */

#include "curve.h"

mrb_value siren_parabola_new(mrb_state* mrb, const Handle(Geom_Curve)* curve)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  mrb_value obj;
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Parabola")));
  void* p = mrb_malloc(mrb, sizeof(Handle(Geom_Curve)));
  Handle(Geom_Curve)* hgcurve = new(p) Handle(Geom_Curve)();
  *hgcurve = *curve;
  DATA_PTR(obj) = hgcurve;
  DATA_TYPE(obj) = &siren_parabola_type;
  return obj;
}

Handle(Geom_Parabola) siren_parabola_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *static_cast<Handle(Geom_Curve)*>(mrb_get_datatype(mrb, self, &siren_parabola_type));
  if (hgc.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Curve."); }
  Handle(Geom_Parabola) parabola = Handle(Geom_Parabola)::DownCast(hgc);
  if (parabola.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Parabola."); }
  return parabola;
}

bool siren_parabola_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_curve = siren_curve_rclass(mrb);
  struct RClass* cls_parabola = mrb_define_class_under(mrb, mod_siren, "Parabola", cls_curve);
  MRB_SET_INSTANCE_TT(cls_parabola, MRB_TT_DATA);
  mrb_define_method(mrb, cls_parabola, "initialize", siren_curve_init, MRB_ARGS_NONE());
  return true;
}
