#include "brepio.h"

bool mrb_siren_brepio_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "BRepIO");
  mrb_define_class_method(mrb, rclass, "save", mrb_method_name(brepio_save), ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "load", mrb_method_name(brepio_load), ARGS_REQ(1));
  return true;
}

mrb_method(brepio_save)
{
  mrb_value target; 
  mrb_value path;
  int argc = mrb_get_args(mrb, "oS", &target, &path);

  TopoDS_Shape* shape = mrb_siren_get_shape(mrb, target);
  BRepTools::Write(*shape, (Standard_CString)RSTRING_PTR(path));

  return mrb_nil_value();
}

mrb_method(brepio_load)
{
  mrb_value path;
  int argc = mrb_get_args(mrb, "S", &path);

  BRep_Builder B;
  TopoDS_Shape* shape = new TopoDS_Shape();
  BRepTools::Read(*shape, (Standard_CString)RSTRING_PTR(path), B);

  return mrb_siren_shape_new(mrb, shape);
}

