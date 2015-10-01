#include "brepio.h"

bool siren_brepio_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "BRepIO");
  mrb_define_class_method(mrb, rclass, "save", siren_brepio_save, MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "load", siren_brepio_load, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, rclass, "dump", siren_brepio_dump, MRB_ARGS_REQ(1));
  return true;
}

mrb_value siren_brepio_save(mrb_state* mrb, mrb_value self)
{
  mrb_value target; 
  mrb_value path;
  int argc = mrb_get_args(mrb, "oS", &target, &path);

  TopoDS_Shape* shape = siren_shape_get(mrb, target);
  if (BRepTools::Write(*shape, (Standard_CString)RSTRING_PTR(path)) != Standard_True) {
    static const char m[] = "Failed to write BRep file.";
    return mrb_exc_new(mrb, E_ARGUMENT_ERROR, m, sizeof(m) - 1);
  }
  return mrb_nil_value();
}

mrb_value siren_brepio_load(mrb_state* mrb, mrb_value self)
{
  mrb_value path;
  int argc = mrb_get_args(mrb, "S", &path);

  BRep_Builder B;
  TopoDS_Shape shape;
  if (BRepTools::Read(shape, (Standard_CString)RSTRING_PTR(path), B) != Standard_True) {
    static const char m[] = "Failed to read BRep file.";
    return mrb_exc_new(mrb, E_ARGUMENT_ERROR, m, sizeof(m) - 1);
  }

  return siren_shape_new(mrb, shape);
}

mrb_value siren_brepio_dump(mrb_state* mrb, mrb_value self)
{
  mrb_value target; 
  int argc = mrb_get_args(mrb, "o", &target);
  TopoDS_Shape* shape = siren_shape_get(mrb, target);
  BRepTools::Dump(*shape, std::cout);
  return mrb_nil_value();
}

