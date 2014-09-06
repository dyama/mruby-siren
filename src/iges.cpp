#include "iges.h"

bool siren_iges_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "IGES");
  mrb_define_class_method(mrb, rclass, "save", siren_iges_save, ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "load", siren_iges_load, ARGS_REQ(1));
  return true;
}

mrb_value siren_iges_save(mrb_state* mrb, mrb_value self)
{
  mrb_value shapes;
  mrb_value path;
  int argc = mrb_get_args(mrb, "AS", &shapes, &path);

  IGESControl_Controller::Init();
  IGESControl_Writer writer(Interface_Static::CVal("XSTEP.iges.unit"),
    Interface_Static::IVal("XSTEP.iges.writebrep.mode"));

  for (int i=0; i < mrb_ary_len(mrb, shapes); i++) {
    mrb_value target = mrb_ary_ref(mrb, shapes, i);
    TopoDS_Shape* shape = siren_shape_get(mrb, target);
    writer.AddShape(*shape);
  }

  writer.ComputeModel();

  if (writer.Write((Standard_CString)RSTRING_PTR(path)) == Standard_False) {
    static const char m[] = "Save error.";
    return mrb_exc_new(mrb, E_ARGUMENT_ERROR, m, sizeof(m) - 1);
  }

  return mrb_nil_value();
}

mrb_value siren_iges_load(mrb_state* mrb, mrb_value self)
{
  mrb_value path;
  mrb_bool oneshape;
  int argc = mrb_get_args(mrb, "S|b", &path, &oneshape);

  IGESControl_Reader iges_reader;
  int stat = iges_reader.ReadFile((Standard_CString)RSTRING_PTR(path));
  mrb_value result;

  if (stat == IFSelect_RetDone) {
    try {
      iges_reader.TransferRoots();
    }
    catch (...) {
      static const char m[] = "Failed to TransferRoots() with an IGES file.";
      return mrb_exc_new(mrb, E_RUNTIME_ERROR, m, sizeof(m) - 1);
    }

    if (oneshape) {
      // As one shape
      TopoDS_Shape* shape = siren_occ_shape_new(mrb);
      *shape = iges_reader.OneShape();
      result = siren_shape_new(mrb, shape);
    }
    else {
      // Some shapes
      result = mrb_ary_new(mrb);
      for (int i=1; i <= iges_reader.NbShapes(); i++) {
        try {
          TopoDS_Shape* shape = siren_occ_shape_new(mrb);
          *shape = iges_reader.Shape(i);
          mrb_value mrshape = siren_shape_new(mrb, shape);
          mrb_ary_push(mrb, result, mrshape);
        }
        catch(...) {
          // Add nil value at raise exception.
          mrb_ary_push(mrb, result, mrb_nil_value());
        }
      }
      if (mrb_ary_len(mrb, result) < 1)
        result = mrb_nil_value();
    }
  }
  else {
    static const char m[] = "Failed to load IGES file.";
    result = mrb_exc_new(mrb, E_ARGUMENT_ERROR, m, sizeof(m) - 1);
  }
  return result;
}

