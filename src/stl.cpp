#include "stl.h"

bool siren_stl_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "STL");
  // mrb_define_class_method(mrb, rclass, "save", siren_stl_save, ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "load", siren_stl_load, ARGS_REQ(1));
  return true;
}

// mrb_value siren_stl_save(mrb_state* mrb, mrb_value self)
// {
//   mrb_value shapes;
//   mrb_value path;
//   int argc = mrb_get_args(mrb, "AS", &shapes, &path);
// 
//   stlControl_Controller::Init();
//   stlControl_Writer writer(Interface_Static::CVal("XSTEP.stl.unit"),
//     Interface_Static::IVal("XSTEP.stl.writebrep.mode"));
// 
//   for (int i=0; i < mrb_ary_len(mrb, shapes); i++) {
//     mrb_value target = mrb_ary_ref(mrb, shapes, i);
//     TopoDS_Shape* shape = siren_shape_get(mrb, target);
//     writer.AddShape(*shape);
//   }
// 
//   writer.ComputeModel();
// 
//   if (writer.Write((Standard_CString)RSTRING_PTR(path)) == Standard_False) {
//     static const char m[] = "Save error.";
//     return mrb_exc_new(mrb, E_ARGUMENT_ERROR, m, sizeof(m) - 1);
//   }
// 
//   return mrb_nil_value();
// }

mrb_value siren_stl_load(mrb_state* mrb, mrb_value self)
{
  mrb_value path;
  int argc = mrb_get_args(mrb, "S", &path);

  TopoDS_Shape shape;
  StlAPI_Reader reader;
  reader.Read(shape, (Standard_CString)RSTRING_PTR(path));

  return siren_shape_new(mrb, shape);
}

