#include "heal.h"

bool siren_heal_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Heal");
  // Class method
  mrb_define_class_method(mrb, rclass, "outerwire", siren_heal_outerwire, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "fix", siren_heal_fix, MRB_ARGS_REQ(1));
  // For mix-in
  mrb_define_method      (mrb, rclass, "outerwire", siren_heal_outerwire, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_method      (mrb, rclass, "fix", siren_heal_fix, MRB_ARGS_REQ(1));
  return true;
}

mrb_value siren_heal_outerwire(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  mrb_float tol = 1.0e-1;
  int argc = mrb_get_args(mrb, "o|f", &target, &tol);

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
    ShapeAnalysis_FreeBounds safb(*shape, tol);
    TopoDS_Compound comp = safb.GetClosedWires();
    res = siren_shape_new(mrb, comp);
  }
  return res;
}

mrb_value siren_heal_fix(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  int argc = mrb_get_args(mrb, "o", &target);
  TopoDS_Shape* shape = siren_shape_get(mrb, target);
  mrb_value res = mrb_nil_value();

  Handle(ShapeFix_Shape) sfs = new ShapeFix_Shape();
  sfs->Init(*shape);
  sfs->SetPrecision(1.0);
  sfs->SetMinTolerance(1.0e-6);
  sfs->SetMaxTolerance(1.0e-1);

  switch (shape->ShapeType()) {
    case TopAbs_SOLID:
      sfs->FixSolidTool()->FixShellMode() = 1;
    case TopAbs_SHELL:
      sfs->FixShellTool()->FixFaceMode() = 1;
      sfs->FixShellTool()->FixOrientationMode() = 1;
    case TopAbs_FACE:
      sfs->FixFaceTool()->FixAddNaturalBoundMode() = 1;
      sfs->FixFaceTool()->FixIntersectingWiresMode() = 1;
      sfs->FixFaceTool()->FixLoopWiresMode() = 1;
      sfs->FixFaceTool()->FixOrientationMode() = 1;
      sfs->FixFaceTool()->FixPeriodicDegeneratedMode() = 1;
      sfs->FixFaceTool()->FixSmallAreaWireMode() = 1;
      sfs->FixFaceTool()->FixSplitFaceMode() = 1;
      sfs->FixFaceTool()->FixWireMode() = 1;
    case TopAbs_WIRE:
      //sfs->FixWireTool()->FixAddCurve3dMode() = 1;
      //sfs->FixWireTool()->FixAddPCurveMode() = 1;
      sfs->FixWireTool()->FixConnectedMode() = 1;
      sfs->FixWireTool()->FixDegeneratedMode() = 1;
      sfs->FixWireTool()->FixEdgeCurvesMode() = 1;
      //sfs->FixWireTool()->FixGaps2dMode() = 1;
      sfs->FixWireTool()->FixGaps3dMode() = 1;
      sfs->FixWireTool()->FixGapsByRangesMode() = 1;
      sfs->FixWireTool()->FixIntersectingEdgesMode() = 1;
      sfs->FixWireTool()->FixLackingMode() = 1;
      sfs->FixWireTool()->FixNonAdjacentIntersectingEdgesMode() = 1;
      sfs->FixWireTool()->FixNotchedEdgesMode() = 1;
      //sfs->FixWireTool()->FixRemoveCurve3dMode() = 1;
      //sfs->FixWireTool()->FixRemovePCurveMode() = 1;
      sfs->FixWireTool()->FixReorderMode() = 1;
      //sfs->FixWireTool()->FixReversed2dMode() = 1;
      sfs->FixWireTool()->FixSameParameterMode() = 1;
      sfs->FixWireTool()->FixSeamMode() = 1;
      sfs->FixWireTool()->FixSelfIntersectingEdgeMode() = 1;
      sfs->FixWireTool()->FixSelfIntersectionMode() = 1;
      sfs->FixWireTool()->FixShiftedMode() = 1;
      sfs->FixWireTool()->FixSmallMode() = 1;
      sfs->FixWireTool()->FixVertexToleranceMode() = 1;
    default:
      sfs->FixVertexPositionMode() = 1;
  }

  sfs->Perform();

  TopoDS_Shape fixedshape = sfs->Shape();
  if (!fixedshape.IsNull()) {
    res = siren_shape_new(mrb, fixedshape);
  }

  return res;
}

