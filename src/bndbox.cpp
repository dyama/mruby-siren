#include "bndbox.h"

mrb_value siren_bndbox_new(mrb_state* mrb, const TopoDS_Shape& shape)
{
  mrb_value obj;
  obj = mrb_instance_alloc(mrb, mrb_obj_value(mrb_class_get(mrb, "BndBox")));
  void* p = mrb_malloc(mrb, sizeof(Bnd_Box));
  Bnd_Box* inner = new(p) Bnd_Box();
  BRepBndLib::Add(shape, *inner);
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
  mrb_define_method(mrb, rclass, "initialize", siren_bndbox_init,   MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "inspect",    siren_bndbox_to_s,   MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_s",       siren_bndbox_to_s,   MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "min",        siren_bndbox_min,    MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "max",        siren_bndbox_max,    MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "out?",       siren_bndbox_is_out, MRB_ARGS_REQ(1));
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

mrb_value siren_bndbox_to_s(mrb_state* mrb, mrb_value self)
{
  Bnd_Box* b = siren_bndbox_get(mrb, self);
  char str[128];
  Standard_Real xmin, ymin, zmin, xmax, ymax, zmax;
  b->Get(xmin, ymin, zmin, xmax, ymax, zmax);
  snprintf(str, sizeof(str),
      "#BndBox<xmin=%f, ymin=%f, zmin=%f, xmax=%f, ymax=%f, zmax=%f>",
      xmin, ymin, zmin, xmax, ymax, zmax);
  return mrb_str_new_cstr(mrb, str);
}

mrb_value siren_bndbox_min(mrb_state* mrb, mrb_value self)
{
  Bnd_Box* b = siren_bndbox_get(mrb, self);

  Standard_Real xmin, ymin, zmin;
  Standard_Real xmax, ymax, zmax;

  b->Get(xmin, ymin, zmin, xmax, ymax, zmax);
  return siren_vec_new(mrb, xmin, ymin, zmin);
}

mrb_value siren_bndbox_max(mrb_state* mrb, mrb_value self)
{
  Bnd_Box* b = siren_bndbox_get(mrb, self);

  Standard_Real xmin, ymin, zmin;
  Standard_Real xmax, ymax, zmax;

  b->Get(xmin, ymin, zmin, xmax, ymax, zmax);
  return siren_vec_new(mrb, xmax, ymax, zmax);
}

mrb_value siren_bndbox_is_out(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  Bnd_Box* b = siren_bndbox_get(mrb, self);
  // return b->IsOut(siren_pnt_get(mrb, other)) == Standard_True ? mrb_true_value() : mrb_false_value();
  return b->IsOut(*siren_bndbox_get(mrb, other)) == Standard_True ? mrb_true_value() : mrb_false_value();
}

