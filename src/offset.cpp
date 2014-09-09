#include "offset.h"

bool siren_offset_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Offset");
  mrb_define_class_method(mrb, rclass, "sweep_vec",  siren_offset_sweep_vec,  ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "sweep_path", siren_offset_sweep_path, ARGS_REQ(2) | ARGS_OPT(4));
  mrb_define_class_method(mrb, rclass, "loft",       siren_offset_loft,       ARGS_REQ(1) | ARGS_OPT(3));
  mrb_define_class_method(mrb, rclass, "offset",     siren_offset_offset,     ARGS_REQ(2) | ARGS_OPT(1));
  return true;
}

mrb_value siren_offset_sweep_vec(mrb_state* mrb, mrb_value self)
{
  mrb_value target, vec;
  int argc = mrb_get_args(mrb, "oo", &target, &vec);

  TopoDS_Shape* profile = siren_shape_get(mrb, target);

  gp_Pnt _pt = gp_Pnt(0., 0., 0.).Transformed(profile->Location());

  TopoDS_Edge pe = BRepBuilderAPI_MakeEdge(_pt, siren_pnt_get(mrb, vec));
  TopoDS_Wire path = BRepBuilderAPI_MakeWire(pe);

  BRepOffsetAPI_MakePipe mp(path, *profile);
  mp.Build();

  return siren_shape_new(mrb, mp.Shape());
}

mrb_value siren_offset_sweep_path(mrb_state* mrb, mrb_value self)
{
  mrb_value target, pathwire;
  mrb_bool cont, corr;
  mrb_float scale_first, scale_last;
  int argc = mrb_get_args(mrb, "oo|bbff", &target, &pathwire, &cont, &corr, &scale_first, &scale_last);

  TopoDS_Shape* shape_profile = siren_shape_get(mrb, target);
  TopoDS_Shape* shape_path = siren_shape_get(mrb, pathwire);

  TopoDS_Wire path;

  if (shape_path->ShapeType() == TopAbs_EDGE) {
    path = BRepBuilderAPI_MakeWire(TopoDS::Edge(*shape_path));
  }
  else if (shape_path->ShapeType() == TopAbs_WIRE) {
    path = TopoDS::Wire(*shape_path);
  }
  else {
    static const char m[] = "Path object is not Edge or Wire.";
    return mrb_exc_new(mrb, E_ARGUMENT_ERROR, m, sizeof(m) - 1);
  }

  mrb_value result = mrb_nil_value();

  if (argc >= 3 && argc <= 6) {

    Standard_Boolean withContact = (Standard_Boolean)cont;
    Standard_Boolean withCorrection = (Standard_Boolean)corr;

    BRepOffsetAPI_MakePipeShell ps(path);

    // get params
    Standard_Real fparam, lparam;
    {
      BRepAdaptor_CompCurve cc(path);
      fparam = cc.FirstParameter();
      lparam = cc.LastParameter();
    }

    if (argc < 6) {
      scale_last  = 1.0;
      if (argc < 5) {
        scale_first = 1.0;
      }
    }

    //Handle(Law_Linear) law = new Law_Linear();
    //law->Set(fparam, scale_first, lparam, scale_last);

    Handle(Law_S) law = new Law_S();
    law->Set(fparam, scale_first, lparam, scale_last);

    //Handle(Law_Composite) law = new Law_Composite(fparam, lparam, 1.0e-6);

    // get start point
    TopoDS_Vertex pfirst; {
      TopoDS_Vertex plast;
      TopExp::Vertices(path, pfirst, plast);
    }

    ps.SetLaw(
        *shape_profile, // セクションプロファイル
        law,           // 掃引規則
        pfirst,        // 開始点
        withContact,   // translate profile to start point
        withCorrection // Change normal of profile by curveture
        );

    ps.Build();
    result = siren_shape_new(mrb, ps.Shape());
  }
  else {
    BRepOffsetAPI_MakePipe mp(path, *shape_profile);
    mp.Build();
    result = siren_shape_new(mrb, mp.Shape());
  }
  return result;
}

mrb_value siren_offset_loft(mrb_state* mrb, mrb_value self)
{
  mrb_value objs;
  mrb_bool smooth, is_solid, is_ruled;
  int argc = mrb_get_args(mrb, "A|bbb", &objs, &smooth,  &is_solid, &is_ruled);
  int lsize = mrb_ary_len(mrb, objs);

  if (lsize < 2) {
    static const char m[] = "Number of objects must be over 2 lines.";
    return mrb_exc_new(mrb, E_ARGUMENT_ERROR, m, sizeof(m) - 1);
  }

  Standard_Boolean is_sm, is_s, is_r;
  is_sm = argc < 2 ? Standard_True : (Standard_Boolean)smooth;
  is_s = argc < 3 ? Standard_False : (Standard_Boolean)is_solid;
  is_r = argc < 4 ? Standard_True : (Standard_Boolean)is_ruled;

  BRepOffsetAPI_ThruSections ts(is_s, is_r);

  for (int i=0; i<lsize; i++) {
    mrb_value line = mrb_ary_ref(mrb, objs, i);
    TopoDS_Shape* shape = siren_shape_get(mrb, line);
    TopoDS_Wire w = TopoDS::Wire(*shape);
    ts.AddWire(w);
  }

  ts.SetSmoothing(is_sm);
  ts.Build();

  return siren_shape_new(mrb, ts.Shape());
}

mrb_value siren_offset_offset(mrb_state* mrb, mrb_value self)
{
  mrb_value target;
  mrb_float offset, tol;
  int argc = mrb_get_args(mrb, "of|f", &target, &offset, &tol);
  Standard_Real t = 1.0;
  if (argc == 3)
    t = (Standard_Real)tol;

  TopoDS_Shape* shape = siren_shape_get(mrb, target);

  TopoDS_Compound comp;
  BRep_Builder B;
  B.MakeCompound(comp);

  TopExp_Explorer exp(*shape, TopAbs_FACE);

  for (; exp.More(); exp.Next()) {
    TopoDS_Face face = TopoDS::Face(exp.Current());
    Handle(Geom_Surface) gs = BRep_Tool::Surface(face);
    Handle(Geom_OffsetSurface) gos = new Geom_OffsetSurface(gs, (Standard_Real)offset);
    TopoDS_Face newface = BRepBuilderAPI_MakeFace(gos, t);
    B.Add(comp, newface);
  }

  return siren_shape_new(mrb, comp);
}

