#include "prim.h"

bool siren_prim_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Prim");
  mrb_define_class_method(mrb, rclass, "box",      siren_prim_box,      ARGS_REQ(1) | ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "sphere",   siren_prim_sphere,   ARGS_REQ(1) | ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "cylinder", siren_prim_cylinder, ARGS_REQ(5));
  mrb_define_class_method(mrb, rclass, "cone",     siren_prim_cone,     ARGS_REQ(6));
  mrb_define_class_method(mrb, rclass, "torus",    siren_prim_torus,    ARGS_REQ(5));
  return true;
}

mrb_value siren_prim_box(mrb_state* mrb, mrb_value self)
{
  mrb_value size, pos;
  int argc = mrb_get_args(mrb, "A|o", &size, &pos);

  Standard_Real sx, sy, sz;
  sx = (Standard_Real)to_double(mrb_ary_ref(mrb, size, 0));
  sy = (Standard_Real)to_double(mrb_ary_ref(mrb, size, 1));
  sz = (Standard_Real)to_double(mrb_ary_ref(mrb, size, 2));

  gp_Pnt op;
  if (argc == 2) {
    gp_Vec* v = siren_vec_get(mrb, pos);
    op = gp_Pnt(v->X(), v->Y(), v->Z());
  }
  else {
    op = gp_Pnt(0., 0., 0.);
  }

  BRepPrimAPI_MakeBox api(op, sx, sy, sz);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_sphere(mrb_state* mrb, mrb_value self)
{
  mrb_float r;
  mrb_value pos;
  int argc = mrb_get_args(mrb, "f|o", &r, &pos);

  gp_Pnt op;
  if (argc == 2) {
    gp_Vec* v = siren_vec_get(mrb, pos);
    op = gp_Pnt(v->X(), v->Y(), v->Z());
  }
  else {
    op = gp_Pnt(0., 0., 0.);
  }

  BRepPrimAPI_MakeSphere api(op, (Standard_Real)r); 
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_cylinder(mrb_state* mrb, mrb_value self)
{
  mrb_value pos, norm;
  mrb_float r, h, a;
  int argc = mrb_get_args(mrb, "oofff", &pos, &norm, &r, &h, &a);

  gp_Vec* vpos = siren_vec_get(mrb, pos);
  gp_Vec* vnorm = siren_vec_get(mrb, norm);
  gp_Ax2 ax(gp_Pnt(vpos->X(), vpos->Y(), vpos->Z()), gp_Dir(vnorm->X(), vnorm->Y(), vnorm->Z()));

  BRepPrimAPI_MakeCylinder api(ax, (Standard_Real)r, (Standard_Real)h, (Standard_Real)a);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_cone(mrb_state* mrb, mrb_value self)
{
  mrb_value pos, norm;
  mrb_float r1, r2, h, ang;
  int argc = mrb_get_args(mrb, "ooffff", &pos, &norm, &r1, &r2, &h, &ang);

  gp_Vec* vpos = siren_vec_get(mrb, pos);
  gp_Vec* vnorm = siren_vec_get(mrb, norm);
  gp_Ax2 ax(gp_Pnt(vpos->X(), vpos->Y(), vpos->Z()), gp_Dir(vnorm->X(), vnorm->Y(), vnorm->Z()));

  BRepPrimAPI_MakeCone api(ax, (Standard_Real)r1, (Standard_Real)r2, (Standard_Real)h, (Standard_Real)ang);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_torus(mrb_state* mrb, mrb_value self)
{
  mrb_float r1, r2, ang;
  mrb_value pos, norm;
  int argc = mrb_get_args(mrb, "oofff", &pos, &norm, &r1, &r2, &ang);

  gp_Vec* vpos = siren_vec_get(mrb, pos);
  gp_Vec* vnorm = siren_vec_get(mrb, norm);
  gp_Ax2 ax(gp_Pnt(vpos->X(), vpos->Y(), vpos->Z()), gp_Dir(vnorm->X(), vnorm->Y(), vnorm->Z()));

  BRepPrimAPI_MakeTorus api(ax, (Standard_Real)r1, (Standard_Real)r2, (Standard_Real)ang);
  return siren_shape_new(mrb, api.Shape());
}

