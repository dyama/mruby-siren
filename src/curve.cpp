/*
 * Document-class: Curve
 *
 */

#include "curve.h"

mrb_value siren_curve_new(mrb_state* mrb, const Handle(Geom_Curve)* curve)
{
  mrb_value obj;
  obj = mrb_instance_alloc(mrb, mrb_obj_value(siren_curve_rclass(mrb)));
  void* p = mrb_malloc(mrb, sizeof(Handle(Geom_Curve)));
  Handle(Geom_Curve)* hgcurve = new(p) Handle(Geom_Curve)();
  *hgcurve = *curve;
  DATA_PTR(obj)  = hgcurve;
  DATA_TYPE(obj) = &siren_curve_type;
  siren_curve_add_singleton_method(mrb, obj);
  return obj;
}

void siren_curve_add_singleton_method(mrb_state* mrb, mrb_value& self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  switch (siren_curve_geomtype_native(hgc)) {
    /*
    case SrCT_BEZIERCURVE:  siren_beziercurve_install(mrb, mrb_obj_ptr(self));  break;
    case SrCT_BSPLINECURVE: siren_bsplinecurve_install(mrb, mrb_obj_ptr(self)); break;
    case SrCT_TRIMMEDCURVE: siren_trimmedcurve_install(mrb, mrb_obj_ptr(self)); break;
    */
    case SrCT_CIRCLE:       siren_circle_install(mrb, mrb_obj_ptr(self));       break;
    /*
    case SrCT_ELLIPSE:      siren_ellipse_install(mrb, mrb_obj_ptr(self));      break;
    case SrCT_HYPERBOLA:    siren_hyperbola_install(mrb, mrb_obj_ptr(self));    break;
    case SrCT_PARABOLA:     siren_parabola_install(mrb, mrb_obj_ptr(self));     break;
    */
    case SrCT_LINE:         siren_line_install(mrb, mrb_obj_ptr(self));         break;
    /*
    case SrCT_OFFSETCURVE:  siren_offsetcurve_install(mrb, mrb_obj_ptr(self));  break;
    case SrCT_COMPLEXCURVE: siren_complexcurve_install(mrb, mrb_obj_ptr(self)); break;
    */
    default: break;
  }
  return;
}

bool siren_curve_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_curve = mrb_define_class_under(mrb, mod_siren, "Curve", mrb->object_class);
  MRB_SET_INSTANCE_TT(cls_curve, MRB_TT_DATA);
  mrb_define_method(mrb, cls_curve, "initialize", siren_curve_init,     MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_curve, "type",       siren_curve_geomtype, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_curve, "inspect",    siren_curve_to_s, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_curve, "to_s",       siren_curve_to_s, MRB_ARGS_NONE());
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

mrb_value siren_curve_geomtype(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  int type = siren_curve_geomtype_native(hgc);
  return mrb_fixnum_value(type);
}

mrb_value siren_curve_to_s(mrb_state* mrb, mrb_value self)
{
  mrb_value str = mrb_str_new_cstr(mrb, "#<Curve:");
  mrb_str_concat(mrb, str, mrb_ptr_to_str(mrb, mrb_cptr(self)));
  mrb_str_cat_lit(mrb, str, " @type=");

  mrb_value type = mrb_funcall(mrb, self, "type", 0);
  struct RClass* cls_curve = siren_curve_rclass(mrb);
  mrb_value curvetype = mrb_funcall(mrb, mrb_obj_value(cls_curve), "typename", 1, type);

  mrb_str_append(mrb, str, curvetype);
  mrb_str_cat_lit(mrb, str, ">");
  return str;
}

