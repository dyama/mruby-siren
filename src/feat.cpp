#include "feat.h"

bool siren_feat_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Feat");
  mrb_define_class_method(mrb, rclass, "splitFxW", siren_feat_splitFxW, ARGS_REQ(2));
  return true;
}

mrb_value siren_feat_splitFxW(mrb_state* mrb, mrb_value self)
{
  mrb_value face, wire;
  int argc = mrb_get_args(mrb, "oo", &face, &wire);

  TopoDS_Shape* sface = siren_shape_get(mrb, face);
  TopoDS_Shape* swire = siren_shape_get(mrb, wire);

  TopoDS_Face _face = TopoDS::Face(*sface);
  BRepFeat_SplitShape splitter(_face);

  TopExp_Explorer ex(*swire, TopAbs_WIRE);
  for (; ex.More(); ex.Next()) {
    TopoDS_Wire e = TopoDS::Wire(ex.Current());
    splitter.Add(e, _face);
  }

  splitter.Build();
  if (!splitter.IsDone()) {
    return mrb_nil_value();
  }

  return siren_shape_new(mrb, splitter.Shape());
}


