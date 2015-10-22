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
  mrb_define_method(mrb, rclass, "initialize", siren_bndbox_init,          MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "inspect",    siren_bndbox_to_s,          MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_s",       siren_bndbox_to_s,          MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "min",        siren_bndbox_min,           MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "max",        siren_bndbox_max,           MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "out?",       siren_bndbox_is_out,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "center",     siren_bndbox_center,        MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "xsize",      siren_bndbox_xsize,         MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "ysize",      siren_bndbox_ysize,         MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "zsize",      siren_bndbox_zsize,         MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "void?",      siren_bndbox_is_void,       MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "whole?",     siren_bndbox_is_whole,      MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "void!",      siren_bndbox_void_bang,     MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "whole!",     siren_bndbox_whole_bang,    MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "xthin?",     siren_bndbox_is_xthin,      MRB_ARGS_OPT(1));
  mrb_define_method(mrb, rclass, "ythin?",     siren_bndbox_is_ythin,      MRB_ARGS_OPT(1));
  mrb_define_method(mrb, rclass, "zthin?",     siren_bndbox_is_zthin,      MRB_ARGS_OPT(1));
  mrb_define_method(mrb, rclass, "openxmin?",  siren_bndbox_is_openxmin,   MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "openxmax?",  siren_bndbox_is_openxmax,   MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "openymin?",  siren_bndbox_is_openymin,   MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "openymax?",  siren_bndbox_is_openymax,   MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "openzmin?",  siren_bndbox_is_openzmin,   MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "openzmax?",  siren_bndbox_is_openzmax,   MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "openxmin!",  siren_bndbox_openxmin_bang, MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "openxmax!",  siren_bndbox_openxmax_bang, MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "openymin!",  siren_bndbox_openymin_bang, MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "openymax!",  siren_bndbox_openymax_bang, MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "openzmin!",  siren_bndbox_openzmin_bang, MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "openzmax!",  siren_bndbox_openzmax_bang, MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "gap",        siren_bndbox_get_gap,       MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "gap=",       siren_bndbox_set_gap,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "dist",       siren_bndbox_dist,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "square",     siren_bndbox_square,        MRB_ARGS_NONE());
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
  return siren_pnt_to_ary(mrb, siren_bndbox_get(mrb, self)->CornerMin());
}

mrb_value siren_bndbox_max(mrb_state* mrb, mrb_value self)
{
  return siren_pnt_to_ary(mrb, siren_bndbox_get(mrb, self)->CornerMax());
}

mrb_value siren_bndbox_is_out(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  Bnd_Box* b = siren_bndbox_get(mrb, self);
  // return b->IsOut(siren_pnt_get(mrb, other)) == Standard_True ? mrb_true_value() : mrb_false_value();
  return b->IsOut(*siren_bndbox_get(mrb, other)) == Standard_True ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_bndbox_center(mrb_state* mrb, mrb_value self)
{
  Bnd_Box* b = siren_bndbox_get(mrb, self);
  Standard_Real xmin, ymin, zmin;
  Standard_Real xmax, ymax, zmax;
  b->Get(xmin, ymin, zmin, xmax, ymax, zmax);
  return siren_pnt_new(mrb, (xmax - xmin) / 2.0, (ymax - ymin) / 2.0, (zmax - zmin) / 2.0);
}

mrb_value siren_bndbox_xsize(mrb_state* mrb, mrb_value self)
{
  Bnd_Box* b = siren_bndbox_get(mrb, self);
  Standard_Real xmin, ymin, zmin;
  Standard_Real xmax, ymax, zmax;
  b->Get(xmin, ymin, zmin, xmax, ymax, zmax);
  return mrb_float_value(mrb, xmax - xmin);
}

mrb_value siren_bndbox_ysize(mrb_state* mrb, mrb_value self)
{
  Bnd_Box* b = siren_bndbox_get(mrb, self);
  Standard_Real xmin, ymin, zmin;
  Standard_Real xmax, ymax, zmax;
  b->Get(xmin, ymin, zmin, xmax, ymax, zmax);
  return mrb_float_value(mrb, ymax - ymin);
}

mrb_value siren_bndbox_zsize(mrb_state* mrb, mrb_value self)
{
  Bnd_Box* b = siren_bndbox_get(mrb, self);
  Standard_Real xmin, ymin, zmin;
  Standard_Real xmax, ymax, zmax;
  b->Get(xmin, ymin, zmin, xmax, ymax, zmax);
  return mrb_float_value(mrb, zmax - zmin);
}

mrb_value siren_bndbox_is_void(mrb_state* mrb, mrb_value self)
{
  return siren_bndbox_get(mrb, self)->IsVoid() ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_bndbox_is_whole(mrb_state* mrb, mrb_value self)
{
  return siren_bndbox_get(mrb, self)->IsWhole() ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_bndbox_void_bang(mrb_state* mrb, mrb_value self)
{
  siren_bndbox_get(mrb, self)->SetVoid();
  return mrb_nil_value();
}

mrb_value siren_bndbox_whole_bang(mrb_state* mrb, mrb_value self)
{
  siren_bndbox_get(mrb, self)->SetWhole();
  return mrb_nil_value();
}

mrb_value siren_bndbox_is_xthin(mrb_state* mrb, mrb_value self)
{
  mrb_float tol;
  int argc = mrb_get_args(mrb, "|f", &tol);
  Bnd_Box* b = siren_bndbox_get(mrb, self);
  return b->IsXThin(argc ? tol : 0.0) ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_bndbox_is_ythin(mrb_state* mrb, mrb_value self)
{
  mrb_float tol;
  int argc = mrb_get_args(mrb, "|f", &tol);
  Bnd_Box* b = siren_bndbox_get(mrb, self);
  return b->IsYThin(argc ? tol : 0.0) ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_bndbox_is_zthin(mrb_state* mrb, mrb_value self)
{
  mrb_float tol;
  int argc = mrb_get_args(mrb, "|f", &tol);
  Bnd_Box* b = siren_bndbox_get(mrb, self);
  return b->IsZThin(argc ? tol : 0.0) ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_bndbox_is_openxmin(mrb_state* mrb, mrb_value self)
{
  return siren_bndbox_get(mrb, self)->IsOpenXmin() ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_bndbox_is_openxmax(mrb_state* mrb, mrb_value self)
{
  return siren_bndbox_get(mrb, self)->IsOpenXmax() ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_bndbox_is_openymin(mrb_state* mrb, mrb_value self)
{
  return siren_bndbox_get(mrb, self)->IsOpenYmin() ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_bndbox_is_openymax(mrb_state* mrb, mrb_value self)
{
  return siren_bndbox_get(mrb, self)->IsOpenYmax() ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_bndbox_is_openzmin(mrb_state* mrb, mrb_value self)
{
  return siren_bndbox_get(mrb, self)->IsOpenZmin() ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_bndbox_is_openzmax(mrb_state* mrb, mrb_value self)
{
  return siren_bndbox_get(mrb, self)->IsOpenZmax() ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_bndbox_openxmin_bang(mrb_state* mrb, mrb_value self)
{
  siren_bndbox_get(mrb, self)->OpenXmin();
  return mrb_nil_value();
}

mrb_value siren_bndbox_openxmax_bang(mrb_state* mrb, mrb_value self)
{
  siren_bndbox_get(mrb, self)->OpenXmax();
  return mrb_nil_value();
}

mrb_value siren_bndbox_openymin_bang(mrb_state* mrb, mrb_value self)
{
  siren_bndbox_get(mrb, self)->OpenYmin();
  return mrb_nil_value();
}

mrb_value siren_bndbox_openymax_bang(mrb_state* mrb, mrb_value self)
{
  siren_bndbox_get(mrb, self)->OpenYmax();
  return mrb_nil_value();
}

mrb_value siren_bndbox_openzmin_bang(mrb_state* mrb, mrb_value self)
{
  siren_bndbox_get(mrb, self)->OpenZmin();
  return mrb_nil_value();
}

mrb_value siren_bndbox_openzmax_bang(mrb_state* mrb, mrb_value self)
{
  siren_bndbox_get(mrb, self)->OpenZmax();
  return mrb_nil_value();
}

mrb_value siren_bndbox_set_gap(mrb_state* mrb, mrb_value self)
{
  mrb_float tol;
  int argc = mrb_get_args(mrb, "f", &tol);
  siren_bndbox_get(mrb, self)->SetGap(tol);
  return mrb_nil_value();
}

mrb_value siren_bndbox_get_gap(mrb_state* mrb, mrb_value self)
{
  Standard_Real tol = siren_bndbox_get(mrb, self)->GetGap();
  return mrb_float_value(mrb, tol);
}

mrb_value siren_bndbox_dist(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  Standard_Real value = siren_bndbox_get(mrb, self)->Distance(*siren_bndbox_get(mrb, other));
  return mrb_float_value(mrb, value);
}

mrb_value siren_bndbox_square(mrb_state* mrb, mrb_value self)
{
  Standard_Real value = siren_bndbox_get(mrb, self)->SquareExtent();
  return mrb_float_value(mrb, value);
}

