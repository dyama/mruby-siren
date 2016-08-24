#include "face.h"

void siren_face_install(mrb_state* mrb, RObject* o)
{
  mrb_define_singleton_method(mrb, o, "normal", siren_face_normal, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "to_bezier", siren_face_to_bezier, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "split", siren_face_split, MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, o, "triangle", siren_face_triangle, MRB_ARGS_REQ(2));
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
  if (gbssurf.IsNull()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Specified shape is not B-Spline surface.");
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

mrb_value siren_face_split(mrb_state* mrb, mrb_value self)
{
  mrb_value wire;
  int argc = mrb_get_args(mrb, "o", &wire);

  TopoDS_Shape* sface = siren_shape_get(mrb, self);
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

mrb_value siren_face_triangle(mrb_state* mrb, mrb_value self)
{
  mrb_float deflection, angle;
  int argc = mrb_get_args(mrb, "ff", &deflection, &angle);

  TopoDS_Shape* shape = siren_shape_get(mrb, self);

  TopExp_Explorer ex(*shape, TopAbs_FACE);

  mrb_value result = mrb_ary_new(mrb);

  for (; ex.More(); ex.Next()) {

    TopoDS_Face face = TopoDS::Face(ex.Current());
    BRepTools::Update(face);

    BRepMesh_IncrementalMesh imesh(face, deflection, Standard_False, angle);
    imesh.Perform();
    if (!imesh.IsDone()) {
      continue;
    }

    face = TopoDS::Face(imesh.Shape());

    TopLoc_Location loc;
    // Do triangulation
    Handle(Poly_Triangulation) poly = BRep_Tool::Triangulation(face, loc);
    if (poly.IsNull()) {
      continue;
    }

    const Poly_Array1OfTriangle& tris = poly->Triangles();

    for (Standard_Integer i = tris.Lower(); i <= tris.Upper(); i++) {

      const Poly_Triangle& tri = tris.Value(i);

      // Node indexes
      Standard_Integer n1, n2, n3;
      if (face.Orientation() != TopAbs_REVERSED) {
        tri.Get(n1, n2, n3);
      }
      else {
        tri.Get(n3, n2, n1);
      }

      gp_Pnt p1 = poly->Nodes().Value(n1);
      gp_Pnt p2 = poly->Nodes().Value(n2);
      gp_Pnt p3 = poly->Nodes().Value(n3);

      p1.Transform(loc);
      p2.Transform(loc);
      p3.Transform(loc);

      gp_Vec u = gp_Vec(p2.XYZ() - p1.XYZ());
      gp_Vec v = gp_Vec(p3.XYZ() - p1.XYZ());

      gp_Vec norm(
        u.Y() * v.Z() - u.Z() * v.Y(),
        u.Z() * v.X() - u.X() * v.Z(),
        u.X() * v.Y() - u.Y() * v.X());
      if (norm.Magnitude() <= 0) {
        continue;
      }
      norm.Normalize();

      mrb_value trimesh = mrb_ary_new(mrb);
      mrb_ary_push(mrb, trimesh, siren_pnt_to_ary(mrb, p1));
      mrb_ary_push(mrb, trimesh, siren_pnt_to_ary(mrb, p2));
      mrb_ary_push(mrb, trimesh, siren_pnt_to_ary(mrb, p3));
      mrb_ary_push(mrb, trimesh, siren_vec_to_ary(mrb, u));
      mrb_ary_push(mrb, trimesh, siren_vec_to_ary(mrb, v));
      mrb_ary_push(mrb, trimesh, siren_vec_to_ary(mrb, norm));

      mrb_ary_push(mrb, result, trimesh);

    }
  }

  return result;
}
