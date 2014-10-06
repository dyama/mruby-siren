#include "build.h"

bool siren_build_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Build");
  mrb_define_class_method(mrb, rclass, "copy",       siren_build_copy,       ARGS_REQ(1));
  mrb_define_class_method(mrb, rclass, "vertex",     siren_build_vertex,     ARGS_REQ(3));
  mrb_define_class_method(mrb, rclass, "line",       siren_build_line,       ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "polyline",   siren_build_polyline,   ARGS_REQ(1));
  mrb_define_class_method(mrb, rclass, "curve",      siren_build_curve,      ARGS_REQ(1) | ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "wire",       siren_build_wire,       ARGS_REQ(1));
  mrb_define_class_method(mrb, rclass, "plane",      siren_build_plane,      ARGS_REQ(7));
  mrb_define_class_method(mrb, rclass, "polygon",    siren_build_polygon,    ARGS_REQ(1));
  mrb_define_class_method(mrb, rclass, "nurbscurve", siren_build_nurbscurve, ARGS_REQ(4) | ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "beziersurf", siren_build_beziersurf, ARGS_REQ(1) | ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "nurbssurf",  siren_build_nurbssurf,  ARGS_REQ(5) | ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "sewing",     siren_build_sewing,     ARGS_REQ(1) | ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "solid",      siren_build_solid,      ARGS_REQ(1));
  mrb_define_class_method(mrb, rclass, "compound",   siren_build_compound,   ARGS_REQ(1));
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

  TopoDS_Shape shape = BRepBuilderAPI_MakeEdge(
      siren_pnt_get(mrb, sp), siren_pnt_get(mrb, tp));

  return siren_shape_new(mrb, shape);
}

mrb_value siren_build_polyline(mrb_state* mrb, mrb_value self)
{
  mrb_value ary;
  int argc = mrb_get_args(mrb, "A", &ary);

  BRepBuilderAPI_MakePolygon poly;

  for (int i = 0; i < mrb_ary_len(mrb, ary); i++) {
    poly.Add(siren_pnt_get(mrb, mrb_ary_ref(mrb, ary, i)));
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
    pary->SetValue(i+1, siren_pnt_get(mrb, mrb_ary_ref(mrb, pts, i)));
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
        vec.SetValue(i+1, siren_dir_get(mrb, avec));
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

  gp_Pln _pln(siren_ax2_get(mrb, pos, norm, vdir));

  BRepBuilderAPI_MakeFace face(_pln, (Standard_Real)umin, (Standard_Real)umax, (Standard_Real)vmin, (Standard_Real)vmax);

  return siren_shape_new(mrb, face.Shape());
}

mrb_value siren_build_polygon(mrb_state* mrb, mrb_value self)
{
  mrb_value pts;
  int argc = mrb_get_args(mrb, "A", &pts);

  BRepBuilderAPI_MakePolygon mp;

  for (int i=0; i<mrb_ary_len(mrb, pts); i++) {
    mp.Add(siren_pnt_get(mrb, mrb_ary_ref(mrb, pts, i)));
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

mrb_value siren_build_nurbscurve(mrb_state* mrb, mrb_value self)
{
  mrb_int d;
  mrb_value ks, ms, ps, ws;
  int argc = mrb_get_args(mrb, "iAAA|A", &d, &ks, &ms, &ps, &ws);

  int plen = mrb_ary_len(mrb, ps);

  TColgp_Array1OfPnt poles(0, plen - 1);
  TColStd_Array1OfReal weights(0, plen - 1);
  for (int i=0; i < plen; i++) {
    poles.SetValue(i, siren_pnt_get(mrb, mrb_ary_ref(mrb, ps, i)));
    if (argc == 5) {
      mrb_value w = mrb_ary_ref(mrb, ws, i);
      weights.SetValue(i, (Standard_Real)mrb_float(w));
    }
    else {
      weights.SetValue(i, (Standard_Real)1.0);
    }
  }

  int klen = mrb_ary_len(mrb, ks);
  TColStd_Array1OfReal knots(0, klen - 1);
  TColStd_Array1OfInteger mults(0, klen - 1);

  for (int i=0; i < klen; i++) {
    mrb_value knot = mrb_ary_ref(mrb, ks, i);
    knots.SetValue(i, (Standard_Real)mrb_float(knot));
    mrb_value mult = mrb_ary_ref(mrb, ms, i);
    mults.SetValue(i, (Standard_Integer)mrb_fixnum(mult));
  }

  Handle(Geom_BSplineCurve) hgeom_bscurve = new Geom_BSplineCurve(
      poles, weights, knots, mults, (Standard_Integer)d, Standard_False);

  return siren_shape_new(mrb, BRepBuilderAPI_MakeEdge(hgeom_bscurve));
}

mrb_value siren_build_beziersurf(mrb_state* mrb, mrb_value self)
{
  mrb_value ptary, wtary;
  int argc = mrb_get_args(mrb, "A|A", &ptary, &wtary);

  int rlen = mrb_ary_len(mrb, ptary);
  int clen = mrb_ary_len(mrb, mrb_ary_ref(mrb, ptary, 0));

  TColgp_Array2OfPnt poles(0, rlen-1, 0, clen-1);

  for (int r=0; r<rlen; r++) {
    mrb_value ar = mrb_ary_ref(mrb, ptary, r);
    for (int c=0; c<clen; c++) {
      poles.SetValue(r, c, siren_pnt_get(mrb, mrb_ary_ref(mrb, ar, c)));
    }
  }

  Handle(Geom_BezierSurface) s = NULL;

  if (argc == 2) {
    TColStd_Array2OfReal weights(0, rlen-1, 0, clen-1);
    for (int r=0; r<rlen; r++) {
      mrb_value ar = mrb_ary_ref(mrb, wtary, r);
      for (int c=0; c<clen; c++) {
        mrb_value val = mrb_ary_ref(mrb, ar, c);
        weights.SetValue(r, c, (Standard_Real)mrb_float(val));
      }
    }
    s = new Geom_BezierSurface(poles, weights);
  }
  else {
    s = new Geom_BezierSurface(poles);
  }

  return siren_shape_new(mrb, BRepBuilderAPI_MakeFace(s, 1.0e-7));
}

mrb_value siren_build_nurbssurf(mrb_state* mrb, mrb_value self)
{
  mrb_int _udeg, _vdeg;
  mrb_value _ar_ukm, _ar_vkm;
  mrb_value _pol;
  mrb_value _wire;
  int argc = mrb_get_args(mrb, "iAiAA|o", &_udeg, &_ar_ukm, &_vdeg, &_ar_vkm, &_pol, &_wire);

  bool has_contour = argc == 6;

  Standard_Integer udeg = _udeg;
  Standard_Integer nbuknots = mrb_ary_len(mrb, _ar_ukm);
  Standard_Integer nbuknots_pure = 0;
  TColStd_Array1OfReal uknots(1, nbuknots);
  TColStd_Array1OfInteger umults(1, nbuknots);
  for (int i=1; i<=nbuknots; i++) {
    mrb_value item = mrb_ary_ref(mrb, _ar_ukm, i - 1);
    mrb_value knot = mrb_ary_ref(mrb, item, 0);
    mrb_value mult = mrb_ary_ref(mrb, item, 1);
    uknots(i) = mrb_fixnum(knot);
    umults(i) = mrb_fixnum(mult);
    nbuknots_pure += umults(i);
  }
  Standard_Integer nbupoles = nbuknots_pure - udeg - 1;

  Standard_Integer vdeg = _vdeg;
  Standard_Integer nbvknots = mrb_ary_len(mrb, _ar_vkm);
  Standard_Integer nbvknots_pure = 0;
  TColStd_Array1OfReal vknots(1, nbvknots);
  TColStd_Array1OfInteger vmults(1, nbvknots);
  for (int i=1; i<=nbvknots; i++) {
    mrb_value item = mrb_ary_ref(mrb, _ar_vkm, i - 1);
    mrb_value knot = mrb_ary_ref(mrb, item, 0);
    mrb_value mult = mrb_ary_ref(mrb, item, 1);
    vknots(i) = mrb_fixnum(knot);
    vmults(i) = mrb_fixnum(mult);
    nbvknots_pure += vmults(i);
  }
  Standard_Integer nbvpoles = nbvknots_pure - vdeg - 1;

  TColgp_Array2OfPnt   poles  (1, nbupoles, 1, nbvpoles);
  TColStd_Array2OfReal weights(1, nbupoles, 1, nbvpoles);

  for (int v=1; v <= nbvpoles; v++) {
    mrb_value vitem = mrb_ary_ref(mrb, _pol, v - 1);
    for (int u=1; u <= nbupoles; u++) {
      mrb_value uitem = mrb_ary_ref(mrb, vitem, u - 1);
      poles.SetValue(u, v, siren_pnt_get(mrb, mrb_ary_ref(mrb, uitem, 0)));
      weights.SetValue(u, v, (Standard_Real)mrb_float(mrb_ary_ref(mrb, uitem, 1)));
    }
  }

  Handle(Geom_BSplineSurface) hg_bssurf = new Geom_BSplineSurface(poles, weights, uknots, vknots, umults, vmults, udeg, vdeg);
  TopoDS_Shape shape;
  if (has_contour) {
    TopoDS_Shape* s = siren_shape_get(mrb, _wire);
    TopoDS_Wire w = TopoDS::Wire(*s);
    shape = BRepBuilderAPI_MakeFace(hg_bssurf, w, Standard_True);
    // Fix a face
    Handle(ShapeFix_Shape) sfs = new ShapeFix_Shape();
    sfs->Init(shape);
    sfs->FixFaceTool()->FixAddNaturalBoundMode() = 1;
    sfs->FixFaceTool()->FixIntersectingWiresMode() = 1;
    sfs->FixFaceTool()->FixLoopWiresMode() = 1;
    sfs->FixFaceTool()->FixOrientationMode() = 1;
    sfs->FixFaceTool()->FixPeriodicDegeneratedMode() = 1;
    sfs->FixFaceTool()->FixSmallAreaWireMode() = 1;
    sfs->FixFaceTool()->FixSplitFaceMode() = 1;
    sfs->FixFaceTool()->FixWireMode() = 1;
    sfs->SetPrecision(1.0);
    sfs->SetMinTolerance(1.0e-1);
    sfs->SetMaxTolerance(1.0);
    sfs->Perform();
    shape = sfs->Shape();
    // End of fix
  }
  else {
    Standard_Real toldegen = 1.0e-1;
    shape = BRepBuilderAPI_MakeFace(hg_bssurf, toldegen);
  }

  return siren_shape_new(mrb, shape);
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

