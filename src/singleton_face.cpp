#include "singleton_face.h"

void siren_face_install(mrb_state* mrb, RObject* o)
{
  mrb_define_singleton_method(mrb, o, "normal", siren_face_normal, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "to_bezier", siren_face_to_bezier, MRB_ARGS_NONE());
  return;
}

mrb_value siren_face_normal(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* c = siren_shape_get(mrb, self);
  TopoDS_Face f = TopoDS::Face(*c);
  Standard_Real umin, umax, vmin, vmax;
  BRepTools::UVBounds(f, umin, umax, vmin, vmax);
  Handle(Geom_Surface) gsurf = BRep_Tool::Surface(f);
  GeomLProp_SLProps props(gsurf, umin, vmin, 1, 0.01);
  gp_Dir n = props.Normal();
  return siren_vec_new(mrb, n.X(), n.Y(), n.Z());
}

mrb_value siren_face_to_bezier(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);

  TopExp_Explorer ex(*shape, TopAbs_FACE);
  TopoDS_Face face = TopoDS::Face(*shape);
  Handle(Geom_Surface) gsurf  = BRep_Tool::Surface(face);
  Handle(Geom_BSplineSurface) gbssurf = Handle(Geom_BSplineSurface)::DownCast(gsurf);
  if (gbssurf == NULL || gbssurf.IsNull()) {
    static const char m[] = "Specified shape is not B-Spline surface.";
    return mrb_exc_new(mrb, E_ARGUMENT_ERROR, m, sizeof(m) - 1);
  }

  TopoDS_Compound comp;
  BRep_Builder B;
  B.MakeCompound(comp);

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

  return siren_shape_new(mrb, comp);
}

