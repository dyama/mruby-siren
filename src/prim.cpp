#include "prim.h"

bool siren_prim_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Prim");
  mrb_define_class_method(mrb, rclass, "box",       siren_prim_box,       MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "box2p",     siren_prim_box2p,     MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "boxax",     siren_prim_boxax,     MRB_ARGS_REQ(3));
  mrb_define_class_method(mrb, rclass, "sphere",    siren_prim_sphere,    MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "cylinder",  siren_prim_cylinder,  MRB_ARGS_REQ(5));
  mrb_define_class_method(mrb, rclass, "cone",      siren_prim_cone,      MRB_ARGS_REQ(6));
  mrb_define_class_method(mrb, rclass, "torus",     siren_prim_torus,     MRB_ARGS_REQ(5));
  mrb_define_class_method(mrb, rclass, "halfspace", siren_prim_halfspace, MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, rclass, "prism",     siren_prim_prism,     MRB_ARGS_NONE());
  mrb_define_class_method(mrb, rclass, "revol",     siren_prim_revol,     MRB_ARGS_NONE());
  mrb_define_class_method(mrb, rclass, "revolution",siren_prim_revolution,MRB_ARGS_NONE());
  mrb_define_class_method(mrb, rclass, "wedge",     siren_prim_wedge,     MRB_ARGS_NONE());
  return true;
}

mrb_value siren_prim_box(mrb_state* mrb, mrb_value self)
{
  mrb_value size, pos;
  int argc = mrb_get_args(mrb, "A|A", &size, &pos);

  Standard_Real sx, sy, sz;
  siren_ary_to_xyz(mrb, size, sx, sy, sz);

  gp_Pnt op;
  if (argc == 2) {
    Standard_Real px, py, pz;
    siren_ary_to_xyz(mrb, pos, px, py, pz);
    op = gp_Pnt(px, py, pz);
  }
  else {
    op = gp_Pnt(0., 0., 0.);
  }

  BRepPrimAPI_MakeBox api(op, sx, sy, sz);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_box2p(mrb_state* mrb, mrb_value self)
{
  mrb_value p1, p2;
  int argc = mrb_get_args(mrb, "AA", &p1, &p2);

  Standard_Real x1, y1, z1, x2, y2, z2;
  siren_ary_to_xyz(mrb, p1, x1, y1, z1);
  siren_ary_to_xyz(mrb, p2, x2, y2, z2);

  gp_Pnt point1(x1, x1, x1);
  gp_Pnt point2(x2, x2, x2);

  BRepPrimAPI_MakeBox api(point1, point2);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_boxax(mrb_state* mrb, mrb_value self)
{
  mrb_value size, pos, dir;
  int argc = mrb_get_args(mrb, "AAA", &size, &pos, &dir);

  Standard_Real sx, sy, sz;
  siren_ary_to_xyz(mrb, size, sx, sy, sz);

  Standard_Real px, py, pz;
  siren_ary_to_xyz(mrb, pos, px, py, pz);

  Standard_Real dx, dy, dz;
  siren_ary_to_xyz(mrb, dir, dx, dy, dz);

  gp_Ax2 ax(gp_Pnt(px, py, pz), gp_Dir(dx, dy, dz));

  BRepPrimAPI_MakeBox api(ax, sx, sy, sz);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_sphere(mrb_state* mrb, mrb_value self)
{
  mrb_float r;
  mrb_value pos;
  int argc = mrb_get_args(mrb, "f|A", &r, &pos);

  gp_Pnt op;
  if (argc == 2) {
    Standard_Real px, py, pz;
    siren_ary_to_xyz(mrb, pos, px, py, pz);
    op = gp_Pnt(px, py, pz);
  }
  else {
    op = gp_Pnt(0., 0., 0.);
  }

  BRepPrimAPI_MakeSphere api(op, r); 
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_cylinder(mrb_state* mrb, mrb_value self)
{
  mrb_value pos, norm;
  mrb_float r, h, a;
  int argc = mrb_get_args(mrb, "AAfff", &pos, &norm, &r, &h, &a);

  gp_Ax2 ax = siren_ary_to_ax2(mrb, pos, norm);

  BRepPrimAPI_MakeCylinder api(ax, r, h, a);

  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_cone(mrb_state* mrb, mrb_value self)
{
  mrb_value pos, norm;
  mrb_float r1, r2, h, ang;
  int argc = mrb_get_args(mrb, "AAffff", &pos, &norm, &r1, &r2, &h, &ang);

  gp_Ax2 ax = siren_ary_to_ax2(mrb, pos, norm);

  BRepPrimAPI_MakeCone api(ax, r1, r2, h, ang);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_torus(mrb_state* mrb, mrb_value self)
{
  mrb_float r1, r2, ang;
  mrb_value pos, norm;
  int argc = mrb_get_args(mrb, "AAfff", &pos, &norm, &r1, &r2, &ang);

  gp_Ax2 ax = siren_ary_to_ax2(mrb, pos, norm);

  BRepPrimAPI_MakeTorus api(ax, r1, r2, ang);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_halfspace(mrb_state* mrb, mrb_value self)
{
  mrb_value surf, refpnt;
  int argc = mrb_get_args(mrb, "oA", &surf, &refpnt);
  TopoDS_Shape* shape = siren_shape_get(mrb, surf);
  if (shape == NULL || shape->IsNull()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Specified shape is incorrect.");
  }
  TopoDS_Solid solid;
  gp_Pnt pnt = siren_ary_to_pnt(mrb, refpnt);
  if (shape->ShapeType() == TopAbs_FACE) {
    solid = BRepPrimAPI_MakeHalfSpace(TopoDS::Face(*shape), pnt);
  }
  else if (shape->ShapeType() == TopAbs_SHELL) {
    solid = BRepPrimAPI_MakeHalfSpace(TopoDS::Shell(*shape), pnt);
  }
  else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Specified shape type is not FACE or SHELL.");
  }
  return siren_shape_new(mrb, solid);
}

mrb_value siren_prim_prism(mrb_state* mrb, mrb_value self)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented.");
}

mrb_value siren_prim_revol(mrb_state* mrb, mrb_value self)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented.");
}

mrb_value siren_prim_revolution(mrb_state* mrb, mrb_value self)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented.");
}

mrb_value siren_prim_wedge(mrb_state* mrb, mrb_value self)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented.");
}

