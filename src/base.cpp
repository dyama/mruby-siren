#include "base.h"

bool siren_base_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Base");
  mrb_define_class_method(mrb, rclass, "edge2pts",  siren_base_edge2pts,  ARGS_REQ(1) | ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "bs2bzsurf", siren_base_bs2bzsurf, ARGS_REQ(1));
  return true;
}

mrb_value siren_base_edge2pts(mrb_state* mrb, mrb_value self)
{
  mrb_value src;
  mrb_float deflect;
  int argc = mrb_get_args(mrb, "o|f", &src, &deflect);

  TopoDS_Shape* shape = siren_shape_get(mrb, src);

  if (argc != 2) {
    deflect = 1.0e-1;
  }

  mrb_value result = mrb_ary_new(mrb);
  double first_param, last_param;

  TopExp_Explorer exp(*shape, TopAbs_EDGE);
  for(; exp.More(); exp.Next()) {
    TopoDS_Edge edge = TopoDS::Edge(exp.Current());

    BRepAdaptor_Curve adaptor(edge);
    first_param = adaptor.FirstParameter();
    last_param = adaptor.LastParameter();

    GCPnts_UniformDeflection unidef(adaptor, (Standard_Real)deflect);
    if (!unidef.IsDone()) {
      continue;
    }

    mrb_value line = mrb_ary_new(mrb);

    // first point
    gp_Pnt p = adaptor.Value(first_param);
    mrb_ary_push(mrb, line, siren_vec_new(mrb, p.X(), p.Y(), p.Z()));

    for (int i=1; i<=unidef.NbPoints(); i++) {
      p = unidef.Value(i);
      mrb_ary_push(mrb, line, siren_vec_new(mrb, p.X(), p.Y(), p.Z()));
    }

    // last point
    p = adaptor.Value(last_param);
    mrb_ary_push(mrb, line, siren_vec_new(mrb, p.X(), p.Y(), p.Z()));

    mrb_ary_push(mrb, result, line);
  }

  return result;
}

mrb_value siren_base_bs2bzsurf(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  int argc = mrb_get_args(mrb, "o", &target);

  TopoDS_Shape* shape = siren_shape_get(mrb, target);

  TopExp_Explorer ex(*shape, TopAbs_FACE);

  TopoDS_Compound comp;
  BRep_Builder B;
  B.MakeCompound(comp);

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
        B.Add(comp, patch);
      }
    }
  }

  return siren_shape_new(mrb, comp);
}

