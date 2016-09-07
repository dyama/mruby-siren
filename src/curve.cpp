/*
 * Document-class: Curve
 *
 */

#include "curve.h"

mrb_value siren_curve_new(mrb_state* mrb, const Handle(Geom_Curve)* curve)
{
  mrb_value obj;
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  struct RClass* cls_curve = mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Curve")));
  obj = mrb_instance_alloc(mrb, mrb_obj_value(cls_curve));
  void* p = mrb_malloc(mrb, sizeof(Handle(Geom_Curve)));
  Handle(Geom_Curve)* hgcurve = new(p) Handle(Geom_Curve)();
  *hgcurve = *curve;
  DATA_PTR(obj)  = hgcurve;
  DATA_TYPE(obj) = &siren_curve_type;
  return obj;
}

bool siren_curve_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_curve = mrb_define_class_under(mrb, mod_siren, "Curve", mrb->object_class);
  MRB_SET_INSTANCE_TT(cls_curve, MRB_TT_DATA);
  mrb_define_method(mrb, cls_curve, "initialize", siren_curve_init,     MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_curve, "type",       siren_curve_geomtype, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_curve, "inspect",    siren_curve_to_s, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_curve, "to_s",       siren_curve_to_s, MRB_ARGS_NONE());

  // circle
  mrb_define_method(mrb, cls_curve, "radius",  siren_curve_circle_get_radius, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_curve, "radius=", siren_curve_circle_set_radius, MRB_ARGS_NONE());

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
 
mrb_value siren_curve_geomtype(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  //if (!Handle(Geom_BoundedCurve)::DownCast(hgc).IsNull()) {
    if (!Handle(Geom_BezierCurve)::DownCast(hgc).IsNull()) {
      return mrb_fixnum_value(1);
    }
    if (!Handle(Geom_BSplineCurve)::DownCast(hgc).IsNull()) {
      return mrb_fixnum_value(2);
    }
    if (!Handle(Geom_TrimmedCurve)::DownCast(hgc).IsNull()) {
      return mrb_fixnum_value(3);
    }
  //  return mrb_fixnum_value(4);
  //}
  //if (!Handle(Geom_Conic)::DownCast(hgc).IsNull()) {
    if (!Handle(Geom_Circle)::DownCast(hgc).IsNull()) {
      return mrb_fixnum_value(5);
    }
    if (!Handle(Geom_Ellipse)::DownCast(hgc).IsNull()) {
      return mrb_fixnum_value(6);
    }
    if (!Handle(Geom_Hyperbola)::DownCast(hgc).IsNull()) {
      return mrb_fixnum_value(7);
    }
    if (!Handle(Geom_Parabola)::DownCast(hgc).IsNull()) {
      return mrb_fixnum_value(8);
    }
  //  return mrb_fixnum_value(9);
  //}
  if (!Handle(Geom_Line)::DownCast(hgc).IsNull()) {
    return mrb_fixnum_value(10);
  }
  if (!Handle(Geom_OffsetCurve)::DownCast(hgc).IsNull()) {
    return mrb_fixnum_value(11);
  }
  if (!Handle(ShapeExtend_ComplexCurve)::DownCast(hgc).IsNull()) {
    return mrb_fixnum_value(12);
  }
  return mrb_fixnum_value(0);
}

mrb_value siren_curve_to_s(mrb_state* mrb, mrb_value self)
{
  mrb_value str = mrb_str_new_cstr(mrb, "#<Curve:");
  mrb_str_concat(mrb, str, mrb_ptr_to_str(mrb, mrb_cptr(self)));
  mrb_str_cat_lit(mrb, str, " @type=");
  mrb_value type = mrb_funcall(mrb, self, "type", 0);
  mrb_value stype = mrb_funcall(mrb, type, "to_gcname", 0);
  mrb_str_append(mrb, str, stype);
  mrb_str_cat_lit(mrb, str, ">");
  return str;
}

mrb_value siren_curve_circle_get_radius(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_Circle) circle = Handle(Geom_Circle)::DownCast(hgc);
  if (circle.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not circle.");
  }
  Standard_Real r = circle->Radius();
  return mrb_float_value(mrb, r);
}

mrb_value siren_curve_circle_set_radius(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_Circle) circle = Handle(Geom_Circle)::DownCast(hgc);
  if (circle.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not circle.");
  }
  mrb_float r;
  int argc = mrb_get_args(mrb, "f", &r);
  circle->SetRadius(r);
  return mrb_nil_value();
}
