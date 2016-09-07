#include "stl.h"

bool siren_stl_install(mrb_state* mrb, struct RClass* rclass)
{
  // Class method
  mrb_define_class_method(mrb, rclass, "load_stl", siren_stl_load, MRB_ARGS_REQ(1));
  // For mix-in
  mrb_define_method      (mrb, rclass, "load_stl", siren_stl_load, MRB_ARGS_REQ(1));
  return true;
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

