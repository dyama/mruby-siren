#include "bool.h"

bool siren_bool_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Bool");
  mrb_define_class_method(mrb, rclass, "common", siren_bool_common, ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "fuse",   siren_bool_fuse,   ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "cut",    siren_bool_cut,    ARGS_REQ(2));
  return true;
}

mrb_value siren_bool_common(mrb_state* mrb, mrb_value self)
{
  mrb_value s1, s2;
  int argc = mrb_get_args(mrb, "oo", &s1, &s2);

  TopoDS_Shape* S1 = siren_shape_get(mrb, s1);
  TopoDS_Shape* S2 = siren_shape_get(mrb, s2);

  BRepAlgoAPI_Common bo(*S1, *S2);
  bo.SetOperation(BOPAlgo_COMMON);
  bo.Build();
  if (bo.ErrorStatus())
    return mrb_nil_value();

  TopoDS_Shape* shape = siren_occ_shape_new(mrb);
  *shape = bo.Shape();

  return siren_shape_new(mrb, shape);
}

mrb_value siren_bool_fuse(mrb_state* mrb, mrb_value self)
{
  mrb_value s1, s2;
  int argc = mrb_get_args(mrb, "oo", &s1, &s2);

  TopoDS_Shape* S1 = siren_shape_get(mrb, s1);
  TopoDS_Shape* S2 = siren_shape_get(mrb, s2);

  BRepAlgoAPI_Common bo(*S1, *S2);
  bo.SetOperation(BOPAlgo_FUSE);
  bo.Build();
  if (bo.ErrorStatus())
    return mrb_nil_value();

  TopoDS_Shape* shape = siren_occ_shape_new(mrb);
  *shape = bo.Shape();

  return siren_shape_new(mrb, shape);
}

mrb_value siren_bool_cut(mrb_state* mrb, mrb_value self)
{
  mrb_value s1, s2;
  int argc = mrb_get_args(mrb, "oo", &s1, &s2);

  TopoDS_Shape* S1 = siren_shape_get(mrb, s1);
  TopoDS_Shape* S2 = siren_shape_get(mrb, s2);

  BRepAlgoAPI_Common bo(*S1, *S2);
  bo.SetOperation(BOPAlgo_CUT);
  bo.Build();
  if (bo.ErrorStatus())
    return mrb_nil_value();

  TopoDS_Shape* shape = siren_occ_shape_new(mrb);
  *shape = bo.Shape();

  return siren_shape_new(mrb, shape);
}

