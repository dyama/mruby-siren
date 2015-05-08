#include "common.h"

/* this function copied from class.c */
mrb_value mrb_instance_alloc(mrb_state *mrb, mrb_value cv)
{
  struct RClass *c = mrb_class_ptr(cv);
  struct RObject *o;
  enum mrb_vtype ttype = MRB_INSTANCE_TT(c);

  if (c->tt == MRB_TT_SCLASS)
    mrb_raise(mrb, E_TYPE_ERROR, "can't create instance of singleton class");

  if (ttype == 0) ttype = MRB_TT_OBJECT;
  o = (struct RObject*)mrb_obj_alloc(mrb, ttype, c);
  return mrb_obj_value(o);
}
/* end of function */

void siren_ary_to_xyz(mrb_state* mrb, mrb_value ary, Standard_Real& x, Standard_Real& y, Standard_Real& z)
{
  x = 0.0; y = 0.0; z = 0.0;
  int len = mrb_ary_len(mrb, ary);
  if (len > 0) {
    mrb_value val = mrb_ary_ref(mrb, ary, 0);
    if (mrb_float_p(val)) {
      x = mrb_float(val);
    }
    else if (mrb_fixnum_p(val)) {
      x = mrb_fixnum(val);
    }
  }
  if (len > 1) {
    mrb_value val = mrb_ary_ref(mrb, ary, 1);
    if (mrb_float_p(val)) {
      y = mrb_float(val);
    }
    else if (mrb_fixnum_p(val)) {
      y = mrb_fixnum(val);
    }
  }
  if (len > 2) {
    mrb_value val = mrb_ary_ref(mrb, ary, 2);
    if (mrb_float_p(val)) {
      z = mrb_float(val);
    }
    else if (mrb_fixnum_p(val)) {
      z = mrb_fixnum(val);
    }
  }
  return;
}

