#include "stl.h"

bool siren_stl_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "STL");
  mrb_define_class_method(mrb, rclass, "save", siren_stl_save, MRB_ARGS_REQ(2) | MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "load", siren_stl_load, MRB_ARGS_REQ(1));
  return true;
}

mrb_value siren_stl_save(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  mrb_value path;
  mrb_value ascii;
  int argc = mrb_get_args(mrb, "oS|b", &target, &path, &ascii);

  TopoDS_Shape* shape = siren_shape_get(mrb, target);

  if (argc == 3) {
    StlAPI::Write(*shape, (Standard_CString)RSTRING_PTR(path), mrb_bool(ascii));
  }
  else {
    StlAPI::Write(*shape, (Standard_CString)RSTRING_PTR(path));
  }

  return mrb_nil_value();
}

mrb_value siren_stl_load(mrb_state* mrb, mrb_value self)
{
  mrb_value path;
  int argc = mrb_get_args(mrb, "S", &path);

  TopoDS_Shape shape;
  StlAPI::Read(shape, (Standard_CString)RSTRING_PTR(path));

  if (shape.IsNull()) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "Failed to load STL from %S.", path);
  }

  return siren_shape_new(mrb, shape);
}

