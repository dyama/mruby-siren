#include "geom.h"

bool siren_geom_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Geom");
  mrb_define_class_method(mrb, rclass, "bs2bzsurf", siren_geom_bs2bzsurf, ARGS_REQ(1));
  return true;
}

mrb_value siren_geom_bs2bzsurf(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  int argc = mrb_get_args(mrb, "o", &target);

  TopoDS_Shape* shape = siren_shape_get(mrb, target);

  TopExp_Explorer ex(*shape, TopAbs_FACE);

  TopoDS_Compound* comp = new TopoDS_Compound();
  BRep_Builder B;
  B.MakeCompound(*comp);

  for (; ex.More(); ex.Next()) {
    TopoDS_Face face = TopoDS::Face(ex.Current());
    Handle(Geom_Surface) gsurf  = BRep_Tool::Surface(face);
    Handle(Geom_BSplineSurface) gbssurf = Handle(Geom_BSplineSurface)::DownCast(gsurf);

    if (gbssurf == NULL || gbssurf.IsNull()) {
      static const char m[] = "Specified shape is not B-Spline surface.";
      return mrb_exc_new(mrb, E_ARGUMENT_ERROR, m, sizeof(m) - 1);
    }

    GeomConvert_BSplineSurfaceToBezierSurface converter(gbssurf);

    TColGeom_Array2OfBezierSurface ary(1, converter.NbUPatches(), 1, converter.NbVPatches());
    converter.Patches(ary);

    for (int r = ary.LowerRow(); r <= ary.UpperRow(); r++) {
      for (int c = ary.LowerCol(); c <= ary.UpperCol(); c++) {
        Handle(Geom_BezierSurface) gbzsurf = ary.Value(r, c);
        TopoDS_Face patch = BRepBuilderAPI_MakeFace(gbzsurf, 1.0e-1);
        B.Add(*comp, patch);
      }
    }
  }

  return siren_shape_new(mrb, comp);
}

