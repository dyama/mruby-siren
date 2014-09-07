#include "bool.h"

bool siren_bool_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Bool");
  mrb_define_class_method(mrb, rclass, "common",   siren_bool_common,   ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "fuse",     siren_bool_fuse,     ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "cut",      siren_bool_cut,      ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "projwire", siren_bool_projwire, ARGS_REQ(3));
  return true;
}

mrb_value siren_bool_common(mrb_state* mrb, mrb_value self)
{
  mrb_value s1, s2;
  int argc = mrb_get_args(mrb, "oo", &s1, &s2);

  TopoDS_Shape* S1 = siren_shape_get(mrb, s1);
  TopoDS_Shape* S2 = siren_shape_get(mrb, s2);

  BRepAlgoAPI_Common api(*S1, *S2);
  api.SetOperation(BOPAlgo_COMMON);
  api.Build();
  if (api.ErrorStatus())
    return mrb_nil_value();

  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_bool_fuse(mrb_state* mrb, mrb_value self)
{
  mrb_value s1, s2;
  int argc = mrb_get_args(mrb, "oo", &s1, &s2);

  TopoDS_Shape* S1 = siren_shape_get(mrb, s1);
  TopoDS_Shape* S2 = siren_shape_get(mrb, s2);

  BRepAlgoAPI_Common api(*S1, *S2);
  api.SetOperation(BOPAlgo_FUSE);
  api.Build();
  if (api.ErrorStatus())
    return mrb_nil_value();

  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_bool_cut(mrb_state* mrb, mrb_value self)
{
  mrb_value s1, s2;
  int argc = mrb_get_args(mrb, "oo", &s1, &s2);

  TopoDS_Shape* S1 = siren_shape_get(mrb, s1);
  TopoDS_Shape* S2 = siren_shape_get(mrb, s2);

  BRepAlgoAPI_Common api(*S1, *S2);
  api.SetOperation(BOPAlgo_CUT);
  api.Build();
  if (api.ErrorStatus())
    return mrb_nil_value();

  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_bool_projwire(mrb_state* mrb, mrb_value self)
{
  mrb_value w, f, v;
  int argc = mrb_get_args(mrb, "ooo", &w, &f, &v);

  TopoDS_Shape* wire = siren_shape_get(mrb, w);
  TopoDS_Shape* face = siren_shape_get(mrb, f);

  gp_Vec* vec = siren_vec_get(mrb, v);
  BRepProj_Projection bpp(*wire, *face, *vec);

  return siren_shape_new(mrb, bpp.Shape());
}

