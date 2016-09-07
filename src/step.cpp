#include "step.h"

#ifdef SIREN_ENABLE_STEP

bool siren_step_install(mrb_state* mrb, struct RClass* mod_siren)
{
  // Class method
  mrb_define_class_method(mrb, mod_siren, "save_step",  siren_step_save, MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, mod_siren, "load_step",  siren_step_load, MRB_ARGS_REQ(1));
  // For mix-in
  mrb_define_method      (mrb, mod_siren, "save_step",  siren_step_save, MRB_ARGS_REQ(2));
  mrb_define_method      (mrb, mod_siren, "load_step",  siren_step_load, MRB_ARGS_REQ(1));
  return true;
}

mrb_value siren_step_save(mrb_state* mrb, mrb_value self)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "This method is not implemented.");
  /*
  mrb_value s;
  mrb_value path;
  int argc = mrb_get_args(mrb, "oS", &s, &path);
  TopoDS_Shape* shape = siren_shape_get(mrb, s);
  STEPControl_Writer writer;
  if (writer.Transfer(*shape, STEPControl_AsIs, Standard_True) != IFSelect_RetDone) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to transfer Shape to STEP entity.");
  }
  if (writer.Write(RSTRING_PTR(path)) != IFSelect_RetDone) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Failed to write STEP to %S.", path);
  }
  */
  return mrb_nil_value();
}

mrb_value siren_step_load(mrb_state* mrb, mrb_value self)
{
  mrb_value path;
  int argc = mrb_get_args(mrb, "S", &path);
  STEPControl_Reader reader;
  if (!reader.ReadFile((Standard_CString)RSTRING_PTR(path))) {
     mrb_raisef(mrb, E_ARGUMENT_ERROR, "Failed to load STEP from %S.", path);
  }
  reader.NbRootsForTransfer();
  reader.TransferRoots();
  return siren_shape_new(mrb, reader.OneShape());
}

#endif
