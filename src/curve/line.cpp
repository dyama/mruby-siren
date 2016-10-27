/**
 * line.cpp
 * Implementation of singleton methods for LINE
 */

#include "curve/line.h"

Handle(Geom_Line) siren_line_get(mrb_state* mrb, mrb_value self)
{
  Handle(Geom_Curve) hgc = *siren_curve_get(mrb, self);
  Handle(Geom_Line) line = Handle(Geom_Line)::DownCast(hgc);
  if (line.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "The curve type is not LINE.");
  }
  return line;
}

bool siren_line_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_curve = siren_curve_rclass(mrb);
  struct RClass* cls_line = mrb_define_class_under(mrb, mod_siren, "Line", cls_curve);
  MRB_SET_INSTANCE_TT(cls_line, MRB_TT_DATA);
  mrb_define_method(mrb, cls_line, "initialize", siren_curve_init, MRB_ARGS_NONE());
  return true;
}

struct RClass* siren_line_rclass(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Line")));
}

