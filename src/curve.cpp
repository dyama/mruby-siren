/*
 * Document-class: Curve
 *
 */

#include "curve.h"

mrb_value siren_curve_new(mrb_state* mrb, const opencascade::handle<Geom_Curve>* curve)
{
  GeomAbs_CurveType type = siren_curve_geomtype_native(*curve);
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  switch (type) {
    case GeomAbs_Line:         return siren_line_new(mrb, curve); break;
    case GeomAbs_Circle:       return siren_circle_new(mrb, curve); break;
    case GeomAbs_Ellipse:      return siren_ellipse_new(mrb, curve); break;
    case GeomAbs_Hyperbola:    return siren_hyperbola_new(mrb, curve); break;
    case GeomAbs_Parabola:     return siren_parabola_new(mrb, curve); break;
    case GeomAbs_BezierCurve:  return siren_bzcurve_new(mrb, curve); break;
    case GeomAbs_BSplineCurve: return siren_bscurve_new(mrb, curve); break;
    case GeomAbs_OffsetCurve:  return siren_offsetcurve_new(mrb, curve); break;
    default: break;
  }
  // rIght?
  mrb_value obj = mrb_instance_alloc(mrb, mrb_obj_value(siren_curve_rclass(mrb)));
  void* p = mrb_malloc(mrb, sizeof(opencascade::handle<Geom_Curve>));
  opencascade::handle<Geom_Curve>* hgcurve = new(p) opencascade::handle<Geom_Curve>();
  *hgcurve = *curve;
  DATA_PTR(obj) = hgcurve;
  DATA_TYPE(obj) = &siren_curve_type;
  return obj;
}

bool siren_curve_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_curve = mrb_define_class_under(mrb, mod_siren, "Curve", mrb->object_class);
  MRB_SET_INSTANCE_TT(cls_curve, MRB_TT_DATA);
  mrb_define_method(mrb, cls_curve, "initialize", siren_curve_init,     MRB_ARGS_NONE());

  // Define derived classes for Siren::Curve
  siren_line_install(mrb, mod_siren);
  siren_circle_install(mrb, mod_siren);
  siren_ellipse_install(mrb, mod_siren);
  siren_hyperbola_install(mrb, mod_siren);
  siren_parabola_install(mrb, mod_siren);
  siren_bzcurve_install(mrb, mod_siren);
  siren_bscurve_install(mrb, mod_siren);
  siren_offsetcurve_install(mrb, mod_siren);

  return true;
}

mrb_value siren_curve_init(mrb_state* mrb, mrb_value self)
{
  mrb_raise(mrb, E_NOMETHOD_ERROR, "private method `new' called for Curve:Class");
  return mrb_nil_value();
}

void siren_curve_final(mrb_state* mrb, void* p)
{
  opencascade::handle<Geom_Curve>* hgcurve = static_cast<opencascade::handle<Geom_Curve>*>(p);
  if (!(*hgcurve).IsNull()) {
    (*hgcurve).Nullify();
  }
  mrb_free(mrb, p);
}

opencascade::handle<Geom_Curve>* siren_curve_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<opencascade::handle<Geom_Curve>*>(mrb_get_datatype(mrb, obj, &siren_curve_type));
}

struct RClass* siren_curve_rclass(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Curve")));
}

