#include "feat.h"

bool siren_feat_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Feat");
  mrb_define_class_method(mrb, rclass, "splitEF", siren_feat_splitEF, ARGS_REQ(2));
  return true;
}

mrb_value siren_feat_splitEF(mrb_state* mrb, mrb_value self)
{
  mrb_value edge, face;
  int argc = mrb_get_args(mrb, "oo", &edge, &face);

  TopoDS_Shape* sedge = siren_shape_get(mrb, edge);
  TopoDS_Shape* sface = siren_shape_get(mrb, face);
  TopoDS_Face _face = TopoDS::Face(*sface);
  BRepFeat_SplitShape splitter(*sface);

  TopExp_Explorer ex(*sedge, TopAbs_EDGE);
  for (; ex.More(); ex.Next()) {
    TopoDS_Edge e = TopoDS::Edge(ex.Current());
    splitter.Add(e, _face);
  }

  splitter.Build();
  if (!splitter.IsDone()) {
    return mrb_nil_value();
  }

  return siren_shape_new(mrb, splitter.Shape());
}


