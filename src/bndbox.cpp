#include "bndbox.h"

/* this function copied from class.c */
static mrb_value
mrb_instance_alloc(mrb_state *mrb, mrb_value cv)
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

mrb_value siren_bndbox_new(mrb_state* mrb, const Bnd_Box& bndbox)
{
  mrb_value obj;
  obj = mrb_instance_alloc(mrb, mrb_obj_value(mrb_class_get(mrb, "BndBox")));
  void* p = mrb_malloc(mrb, sizeof(Bnd_Box));
  Bnd_Box* inner = new(p) Bnd_Box();
  *inner = bndbox; // Copy to inner native member
  DATA_PTR(obj)  = inner;
  DATA_TYPE(obj) = &siren_bndbox_type;
  return obj;
}

Bnd_Box* siren_bndbox_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<Bnd_Box*>(mrb_get_datatype(mrb, obj, &siren_bndbox_type));
}

bool siren_bndbox_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "BndBox", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", siren_bndbox_init,   ARGS_NONE());
  return true;
}

mrb_value siren_bndbox_init(mrb_state* mrb, mrb_value self)
{
  mrb_raise(mrb, E_NOMETHOD_ERROR, "private method `new' called for BndBox:Class");
}

void siren_bndbox_final(mrb_state* mrb, void* p)
{
  Bnd_Box* pp = static_cast<Bnd_Box*>(p);
  mrb_free(mrb, pp);
}

