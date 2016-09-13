#include "iges.h"

#ifdef SIREN_ENABLE_IGES

bool siren_iges_install(mrb_state* mrb, struct RClass* mod_siren)
{
  // Class method
  mrb_define_class_method(mrb, mod_siren, "save_iges", siren_iges_save, MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, mod_siren, "load_iges", siren_iges_load, MRB_ARGS_REQ(1));
  // For mix-in
  mrb_define_method      (mrb, mod_siren, "save_iges", siren_iges_save, MRB_ARGS_REQ(2));
  mrb_define_method      (mrb, mod_siren, "load_iges", siren_iges_load, MRB_ARGS_REQ(1));
  return true;
}

mrb_value siren_iges_save(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  mrb_value path;
  int argc = mrb_get_args(mrb, "oS", &target, &path);

  IGESControl_Controller::Init();
//  IGESControl_Writer writer(Interface_Static::CVal("XSTEP.iges.unit"),
//    Interface_Static::IVal("XSTEP.iges.writebrep.mode"));
  IGESControl_Writer writer(Interface_Static::CVal("XSTEP.iges.unit"), 1);  // the second argument "1" sets the OCCT => IGES conversion method to "BRep"  

  writer.AddShape(*siren_shape_get(mrb, target));
  writer.ComputeModel();

  std::ofstream fst(RSTRING_PTR(path), std::ios_base::out);
  if (writer.Write(fst) == Standard_False) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "Failed to save IGES to %S.", path);
  }

  return mrb_nil_value();
}

mrb_value siren_iges_load(mrb_state* mrb, mrb_value self)
{
  mrb_value path;
  mrb_bool as_ary;
  int argc = mrb_get_args(mrb, "S|b", &path, &as_ary);

  if (argc == 1) {
    as_ary = FALSE;
  }

  IGESControl_Reader iges_reader;
  int stat = iges_reader.ReadFile((Standard_CString)RSTRING_PTR(path));
  mrb_value result;

  if (stat == IFSelect_RetDone) {
    try {
      iges_reader.TransferRoots();
    }
    catch (...) {
      mrb_raise(mrb, E_RUNTIME_ERROR, "Failed to TransferRoots() with an IGES.");
    }

    if (as_ary) {
      // Return array
      result = mrb_ary_new(mrb);
      for (int i=1; i <= iges_reader.NbShapes(); i++) {
        try {
          TopoDS_Shape shape = iges_reader.Shape(i);
          mrb_value mrshape = siren_shape_new(mrb, shape);
          mrb_ary_push(mrb, result, mrshape);
        }
        catch(...) {
          mrb_warn(mrb, "Failed to get entitiy at %d.", i);
        }
      }
      if (mrb_ary_len(mrb, result) < 1) {
        result = mrb_nil_value();
      }
    }
    else {
      // As one shape
      result = siren_shape_new(mrb, iges_reader.OneShape());
    }
  }
  else {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "Failed to load IGES from %S.", path);
  }
  return result;
}

#endif
