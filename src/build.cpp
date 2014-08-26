#include "build.h"

bool mrb_siren_build_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Build");
  mrb_define_class_method(mrb, rclass, "vertex",   mrb_method_name(build_vertex),   ARGS_REQ(3));
  mrb_define_class_method(mrb, rclass, "line",     mrb_method_name(build_line),     ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "compound", mrb_method_name(build_compound), ARGS_REQ(1));
  mrb_define_class_method(mrb, rclass, "polyline", mrb_method_name(build_polyline), ARGS_REQ(1));
  return true;
}

mrb_method(build_vertex)
{
  mrb_float x, y, z;
  int argc = mrb_get_args(mrb, "fff", &x, &y, &z);

  mrb_value res = mrb_class_new_instance(mrb, 0, NULL, mrb_class_get(mrb, "Shape"));
  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, res, mrb_siren_get_shape_type()));

  Standard_Real xx = (Standard_Real)x;
  Standard_Real yy = (Standard_Real)y;
  Standard_Real zz = (Standard_Real)z;

  *shape = BRepBuilderAPI_MakeVertex(gp_Pnt(xx, yy, zz));

  return res;
}

mrb_method(build_line)
{
  mrb_value sp, tp;
  int argc = mrb_get_args(mrb, "oo", &sp, &tp);

  gp_Vec* s = mrb_siren_get_vec(mrb, sp);
  gp_Vec* t = mrb_siren_get_vec(mrb, tp);

  TopoDS_Shape* shape = new TopoDS_Shape();
  *shape = BRepBuilderAPI_MakeEdge(gp_Pnt(s->X(), s->Y(), s->Z()), gp_Pnt(t->X(), t->Y(), t->Z()));

  return mrb_siren_shape_new(mrb, shape);
}

mrb_method(build_polyline)
{
  mrb_value ary;
  int argc = mrb_get_args(mrb, "A", &ary);

  BRepBuilderAPI_MakePolygon poly;

  for (int i = 0; i < mrb_ary_len(mrb, ary); i++) {
    mrb_value item = mrb_ary_ref(mrb, ary, i);
    gp_Vec* v = mrb_siren_get_vec(mrb, item);
    poly.Add(gp_Pnt(v->X(), v->Y(), v->Z()));
  }

  TopoDS_Shape* shape = new TopoDS_Shape();
  *shape = poly.Wire();

  return mrb_siren_shape_new(mrb, shape);
}

mrb_method(build_compound)
{
  mrb_value ary;
  int argc = mrb_get_args(mrb, "A", &ary);

  TopoDS_Compound* comp = new TopoDS_Compound;
  BRep_Builder B;
  B.MakeCompound(*comp);

  for (int i = 0; i < mrb_ary_len(mrb, ary); i++) {
    mrb_value item = mrb_ary_ref(mrb, ary, i);
    TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, item, mrb_siren_get_shape_type()));
    B.Add(*comp, *shape);
  }

  return mrb_siren_shape_new(mrb, comp);
}

