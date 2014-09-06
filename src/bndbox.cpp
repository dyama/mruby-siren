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
  mrb_define_method(mrb, rclass, "initialize", siren_bndbox_init, ARGS_NONE());
  mrb_define_method(mrb, rclass, "min",        siren_bndbox_min,  ARGS_NONE());
  mrb_define_method(mrb, rclass, "max",        siren_bndbox_max,  ARGS_NONE());
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

