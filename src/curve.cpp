/*
 * Document-class: Curve
 *
 */

#include "curve.h"

mrb_value siren_curve_new(mrb_state* mrb, const Handle(Geom_Curve)* curve)
{
  GeomAbs_CurveType type = siren_curve_geomtype_native(*curve);
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  switch (type) {
    case GeomAbs_Line:   return siren_line_new(mrb, curve); break;
    case GeomAbs_Circle: return siren_circle_new(mrb, curve); break;
    default: break;
  }
  mrb_value obj;
  switch (type) {
    case GeomAbs_Ellipse:      obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Ellipse"))); break;
    case GeomAbs_Hyperbola:    obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Hyperbola"))); break;
    case GeomAbs_Parabola:     obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Parabola"))); break;
    case GeomAbs_BezierCurve:  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "BezierCurve"))); break;
    case GeomAbs_BSplineCurve: obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "BSplineCurve"))); break;
    case GeomAbs_OffsetCurve:  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "OffsetCurve"))); break;
    default: obj = mrb_instance_alloc(mrb, mrb_obj_value(siren_curve_rclass(mrb))); break;
  }
  void* p = mrb_malloc(mrb, sizeof(Handle(Geom_Curve)));
  Handle(Geom_Curve)* hgcurve = new(p) Handle(Geom_Curve)();
  *hgcurve = *curve;
  DATA_PTR(obj) = hgcurve;
  switch (type) {
    case GeomAbs_Ellipse:      DATA_TYPE(obj) = &siren_ellipse_type;      break;
    case GeomAbs_Hyperbola:    DATA_TYPE(obj) = &siren_hyperbola_type;    break;
    case GeomAbs_Parabola:     DATA_TYPE(obj) = &siren_parabola_type;     break;
    case GeomAbs_BezierCurve:  DATA_TYPE(obj) = &siren_beziercurve_type;  break;
    case GeomAbs_BSplineCurve: DATA_TYPE(obj) = &siren_bsplinecurve_type; break;
    case GeomAbs_OffsetCurve:  DATA_TYPE(obj) = &siren_offsetcurve_type;  break;
    default: DATA_TYPE(obj) = &siren_curve_type; printf("curvetype"); break;
  }
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
  siren_beziercurve_install(mrb, mod_siren);
  siren_bsplinecurve_install(mrb, mod_siren);
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
  Handle(Geom_Curve)* hgcurve = static_cast<Handle(Geom_Curve)*>(p);
  if (!(*hgcurve).IsNull()) {
    (*hgcurve).Nullify();
  }
  mrb_free(mrb, p);
}

Handle(Geom_Curve)* siren_curve_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<Handle(Geom_Curve)*>(mrb_get_datatype(mrb, obj, &siren_curve_type));
}

struct RClass* siren_curve_rclass(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Curve")));
}

