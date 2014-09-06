#include "algo.h"

bool siren_algo_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Algo");
  mrb_define_class_method(mrb, rclass, "section", siren_algo_section, ARGS_REQ(2));
  return true;
}

mrb_value siren_algo_section(mrb_state* mrb, mrb_value self)
{
  mrb_value s1, s2;
  int argc = mrb_get_args(mrb, "oo", &s1, &s2);

  TopoDS_Shape* S1 = siren_shape_get(mrb, s1);
  TopoDS_Shape* S2 = siren_shape_get(mrb, s2);

  BRepAlgoAPI_Section sect(*S1, *S2, Standard_False );
  sect.ComputePCurveOn1(Standard_True);
  sect.Approximation(Standard_True);
  sect.Build();

  if (!sect.IsDone()) {
    static const char m[] = "Failed to intersection.";
    return mrb_exc_new(mrb, E_ARGUMENT_ERROR, m, sizeof(m) - 1);
  }

  TopoDS_Shape* shape = siren_occ_shape_new(mrb);
  *shape = sect.Shape();

  return siren_shape_new(mrb, shape);
}

