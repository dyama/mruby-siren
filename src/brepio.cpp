#include "brepio.h"

bool siren_brepio_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "BRepIO");
  mrb_define_class_method(mrb, rclass, "save", siren_brepio_save, ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "load", siren_brepio_load, ARGS_REQ(1));
  return true;
}

mrb_value siren_brepio_save(mrb_state* mrb, mrb_value self)
{
  mrb_value target; 
  mrb_value path;
  int argc = mrb_get_args(mrb, "oS", &target, &path);

  TopoDS_Shape* shape = siren_shape_get(mrb, target);
  BRepTools::Write(*shape, (Standard_CString)RSTRING_PTR(path));

  return mrb_nil_value();
}

mrb_value siren_brepio_load(mrb_state* mrb, mrb_value self)
{
  mrb_value path;
  int argc = mrb_get_args(mrb, "S", &path);

  BRep_Builder B;
  TopoDS_Shape* shape = new TopoDS_Shape();
  BRepTools::Read(*shape, (Standard_CString)RSTRING_PTR(path), B);

  return siren_shape_new(mrb, shape);
}

