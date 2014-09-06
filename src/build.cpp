#include "build.h"

bool siren_build_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Build");
  mrb_define_class_method(mrb, rclass, "copy",     siren_build_copy,     ARGS_REQ(1));
  mrb_define_class_method(mrb, rclass, "vertex",   siren_build_vertex,   ARGS_REQ(3));
  mrb_define_class_method(mrb, rclass, "line",     siren_build_line,     ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "polyline", siren_build_polyline, ARGS_REQ(1));
  mrb_define_class_method(mrb, rclass, "curve",    siren_build_curve,    ARGS_REQ(1) | ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "plane",    siren_build_plane,    ARGS_REQ(7));
  mrb_define_class_method(mrb, rclass, "polygon",  siren_build_polygon,  ARGS_REQ(1));
  mrb_define_class_method(mrb, rclass, "sewing",   siren_build_sewing,   ARGS_REQ(1) | ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "solid",    siren_build_solid,    ARGS_REQ(1));
  mrb_define_class_method(mrb, rclass, "compound", siren_build_compound, ARGS_REQ(1));
  return true;
}

mrb_value siren_build_copy(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  int argc = mrb_get_args(mrb, "o", &target);

  TopoDS_Shape* src = siren_shape_get(mrb, target);

  BRepBuilderAPI_Copy B;
  B.Perform(*src);

  return siren_shape_new(mrb, B.Shape());
}

mrb_value siren_build_vertex(mrb_state* mrb, mrb_value self)
{
  mrb_float x, y, z;
  int argc = mrb_get_args(mrb, "fff", &x, &y, &z);

  Standard_Real xx = (Standard_Real)x;
  Standard_Real yy = (Standard_Real)y;
  Standard_Real zz = (Standard_Real)z;

  TopoDS_Shape shape = BRepBuilderAPI_MakeVertex(gp_Pnt(xx, yy, zz));
  return siren_shape_new(mrb, shape);
}

mrb_value siren_build_line(mrb_state* mrb, mrb_value self)
{
  mrb_value sp, tp;
  int argc = mrb_get_args(mrb, "oo", &sp, &tp);

  gp_Vec* s = siren_vec_get(mrb, sp);
  gp_Vec* t = siren_vec_get(mrb, tp);

  TopoDS_Shape shape = BRepBuilderAPI_MakeEdge(gp_Pnt(s->X(), s->Y(), s->Z()), gp_Pnt(t->X(), t->Y(), t->Z()));
  return siren_shape_new(mrb, shape);
}

mrb_value siren_build_polyline(mrb_state* mrb, mrb_value self)
{
  mrb_value ary;
  int argc = mrb_get_args(mrb, "A", &ary);

  BRepBuilderAPI_MakePolygon poly;

  for (int i = 0; i < mrb_ary_len(mrb, ary); i++) {
    mrb_value item = mrb_ary_ref(mrb, ary, i);
    gp_Vec* v = siren_vec_get(mrb, item);
    poly.Add(gp_Pnt(v->X(), v->Y(), v->Z()));
  }

  TopoDS_Shape shape = poly.Wire();
  return siren_shape_new(mrb, shape);
}

mrb_value siren_build_curve(mrb_state* mrb, mrb_value self)
{
  mrb_value pts, vecs;
  int argc = mrb_get_args(mrb, "A|A", &pts, &vecs);

  int psize = mrb_ary_len(mrb, pts);
  Handle(TColgp_HArray1OfPnt) pary = new TColgp_HArray1OfPnt(1, psize);
  for (int i=0; i<psize; i++) {
    mrb_value pt = mrb_ary_ref(mrb, pts, i);
    gp_Vec* pnt = siren_vec_get(mrb, pt);
    pary->SetValue(i+1, gp_Pnt(pnt->X(), pnt->Y(), pnt->Z()));
  }
  GeomAPI_Interpolate intp(pary, Standard_False, 1.0e-7);

  if (argc == 2) {
    TColgp_Array1OfVec vec(1, psize);
    Handle(TColStd_HArray1OfBoolean) use = new TColStd_HArray1OfBoolean(1, psize);

    for (int i=0; i<psize; i++) {
      mrb_value avec = mrb_ary_ref(mrb, vecs, i);
      if (mrb_nil_p(avec)) {
        use->SetValue(i+1, Standard_False); 
      }
      else {
        gp_Vec* vdir = siren_vec_get(mrb, avec);
        gp_Dir dir(vdir->X(), vdir->Y(), vdir->Z());
        vec.SetValue(i+1, dir);
        use->SetValue(i+1, Standard_True);
      }
    }
    intp.Load(vec, use, Standard_True);
  }

  intp.Perform();
  Handle(Geom_BSplineCurve) geSpl = intp.Curve();

  TopoDS_Shape shape = BRepBuilderAPI_MakeEdge(geSpl);
  return siren_shape_new(mrb, shape);
}

mrb_value siren_build_wire(mrb_state* mrb, mrb_value self)
{
  mrb_value objs;
  int argc = mrb_get_args(mrb, "A", &objs);
  ShapeFix_Wire sfw;
  Handle(ShapeExtend_WireData) wd = new ShapeExtend_WireData();
  BRepBuilderAPI_MakeWire mw;
  ShapeFix_ShapeTolerance FTol;
  int osize = mrb_ary_len(mrb, objs);
  for (int i = 0; i < osize ; i++) {
    mrb_value obj = mrb_ary_ref(mrb, objs, i);
    TopoDS_Shape* s = siren_shape_get(mrb, obj);
    if (s->IsNull()) {
      continue;
    }
    TopExp_Explorer exp(*s, TopAbs_EDGE);
    for (; exp.More(); exp.Next()) {
      wd->Add(TopoDS::Edge(exp.Current()));
    }
  }
  if (wd->NbEdges() == 0) {
    return mrb_nil_value();
  }
  sfw.Load(wd);
  sfw.Perform();
  for (int i = 1; i <= sfw.NbEdges(); i ++) {
    TopoDS_Edge e = sfw.WireData()->Edge(i);
    FTol.SetTolerance(e, 0.01, TopAbs_VERTEX);
    mw.Add(e);
  }

  return siren_shape_new(mrb, mw.Shape());
}

mrb_value siren_build_plane(mrb_state* mrb, mrb_value self)
{
  mrb_value pos, norm, vdir;
  mrb_float umin, umax, vmin, vmax;
  int argc = mrb_get_args(mrb, "oooffff", &pos, &norm, &vdir, &umin, &umax, &vmin, &vmax);

  gp_Vec* p = siren_vec_get(mrb, pos);
  gp_Vec* n = siren_vec_get(mrb, norm);
  gp_Vec* d = siren_vec_get(mrb, vdir);

  gp_Pnt _pos(p->X(), p->Y(), p->Z());
  gp_Dir _norm(n->X(), n->Y(), n->Z());
  gp_Dir _vdir(d->X(), d->Y(), d->Z());
  gp_Ax3 ax(_pos, _norm, _vdir);
  gp_Pln _pln(ax);

  BRepBuilderAPI_MakeFace face(_pln, (Standard_Real)umin, (Standard_Real)umax, (Standard_Real)vmin, (Standard_Real)vmax);

  return siren_shape_new(mrb, face.Shape());
}

mrb_value siren_build_polygon(mrb_state* mrb, mrb_value self)
{
  mrb_value pts;
  int argc = mrb_get_args(mrb, "A", &pts);

  BRepBuilderAPI_MakePolygon mp;

  for (int i=0; i<mrb_ary_len(mrb, pts); i++) {
    gp_Vec* v = siren_vec_get(mrb, mrb_ary_ref(mrb, pts, i));
    mp.Add(gp_Pnt(v->X(), v->Y(), v->Z()));
  }

  mp.Close();
  BRepBuilderAPI_MakeFace mf(mp.Wire(), true);
  mf.Build();

  if (!mf.IsDone()) {
    static const char m[] = "Failed to make a polygon.";
    return mrb_exc_new(mrb, E_ARGUMENT_ERROR, m, sizeof(m) - 1);
  }

  return siren_shape_new(mrb, mf.Shape());
}

mrb_value siren_build_sewing(mrb_state* mrb, mrb_value self)
{
  mrb_value ar;
  mrb_float tol;
  int argc = mrb_get_args(mrb, "A|f", &ar, &tol);

  BRepBuilderAPI_Sewing sewer;
  sewer.Init();
  if (argc == 2 && tol >= 0) {
    sewer.SetTolerance(tol);
  }

  int psize = mrb_ary_len(mrb, ar);
  for (int i=0; i<psize; i++) {
    mrb_value item = mrb_ary_ref(mrb, ar, i);
    TopoDS_Shape* shape = siren_shape_get(mrb, item);
    if (shape->IsNull()) {
      continue;
    }
    TopExp_Explorer ex(*shape, TopAbs_FACE);
    for (; ex.More(); ex.Next()) {
      sewer.Add(ex.Current());
    }
  }

  sewer.Perform();

  return siren_shape_new(mrb, sewer.SewedShape());
}

mrb_value siren_build_solid(mrb_state* mrb, mrb_value self)
{
  mrb_value obj;
  int argc = mrb_get_args(mrb, "o", &obj);

  TopoDS_Shape* shape = siren_shape_get(mrb, obj);

  BRepBuilderAPI_MakeSolid solid_maker;

  for (TopExp_Explorer ex(*shape, TopAbs_SHELL); ex.More(); ex.Next()) {
    TopoDS_Shell shell = TopoDS::Shell(ex.Current());
    solid_maker.Add(shell);
  }
  if (!solid_maker.IsDone())
    return mrb_nil_value();

  return siren_shape_new(mrb, solid_maker.Solid());
}

mrb_value siren_build_compound(mrb_state* mrb, mrb_value self)
{
  mrb_value ary;
  int argc = mrb_get_args(mrb, "A", &ary);

  TopoDS_Compound comp;
  BRep_Builder B;
  B.MakeCompound(comp);

  for (int i = 0; i < mrb_ary_len(mrb, ary); i++) {
    TopoDS_Shape* shape = siren_shape_get(mrb, mrb_ary_ref(mrb, ary, i));
    B.Add(comp, *shape);
  }

  return siren_shape_new(mrb, comp);
}

