#include "heal.h"

bool siren_heal_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Heal");
  mrb_define_class_method(mrb, rclass, "outerwire", siren_heal_outerwire, ARGS_REQ(1));
  return true;
}

mrb_value siren_heal_outerwire(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  int argc = mrb_get_args(mrb, "o", &target);

  TopoDS_Shape* shape = siren_shape_get(mrb, target);

  mrb_value res = mrb_nil_value();

  if (shape->ShapeType() == TopAbs_FACE) {
    TopoDS_Face face = TopoDS::Face(*shape);
    TopoDS_Wire wire = ShapeAnalysis::OuterWire(face);
    // ShapeAnalysis_FreeBounds
    // ::ConnectWiresToWires
    res = siren_shape_new(mrb, wire);
  }
  else {
    ShapeAnalysis_FreeBounds safb(*shape, 1.0e+1);
    TopoDS_Compound comp = safb.GetClosedWires();
    res = siren_shape_new(mrb, comp);
  }
  return res;
}

