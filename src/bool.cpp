#include "bool.h"

mrb_value siren_bool_common(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  int argc = mrb_get_args(mrb, "o", &target);
  TopoDS_Shape* S1 = siren_shape_get(mrb, self);
  TopoDS_Shape* S2 = siren_shape_get(mrb, target);
  BRepAlgoAPI_Common api(*S1, *S2);
  api.SetOperation(BOPAlgo_COMMON);
  api.Build();
  if (api.ErrorStatus()) {
    return mrb_nil_value();
  }
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_bool_fuse(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  int argc = mrb_get_args(mrb, "o", &target);
  TopoDS_Shape* S1 = siren_shape_get(mrb, self);
  TopoDS_Shape* S2 = siren_shape_get(mrb, target);
  BRepAlgoAPI_Common api(*S1, *S2);
  api.SetOperation(BOPAlgo_FUSE);
  api.Build();
  if (api.ErrorStatus()) {
    return mrb_nil_value();
  }
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_bool_cut(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  int argc = mrb_get_args(mrb, "o", &target);
  TopoDS_Shape* S1 = siren_shape_get(mrb, self);
  TopoDS_Shape* S2 = siren_shape_get(mrb, target);
  BRepAlgoAPI_Common api(*S1, *S2);
  api.SetOperation(BOPAlgo_CUT);
  api.Build();
  if (api.ErrorStatus()) {
    return mrb_nil_value();
  }
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_bool_projwire(mrb_state* mrb, mrb_value self)
{
  mrb_value w, v;
  int argc = mrb_get_args(mrb, "oo", &w, &v);
  TopoDS_Shape* wire = siren_shape_get(mrb, w);
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  gp_Vec* vec = siren_vec_get(mrb, v);
  BRepProj_Projection api(*wire, *shape, *vec);
  if (!api.IsDone()) {
    return mrb_nil_value();
  }
  return siren_shape_new(mrb, api.Shape());
}

