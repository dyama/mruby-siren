#include "prim.h"

bool siren_prim_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Prim");
  mrb_define_class_method(mrb, rclass, "box",       siren_prim_box,       ARGS_REQ(1) | ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "sphere",    siren_prim_sphere,    ARGS_REQ(1) | ARGS_OPT(1));
  mrb_define_class_method(mrb, rclass, "cylinder",  siren_prim_cylinder,  ARGS_REQ(5));
  mrb_define_class_method(mrb, rclass, "cone",      siren_prim_cone,      ARGS_REQ(6));
  mrb_define_class_method(mrb, rclass, "torus",     siren_prim_torus,     ARGS_REQ(5));
  mrb_define_class_method(mrb, rclass, "halfspace", siren_prim_halfspace, ARGS_NONE());
  mrb_define_class_method(mrb, rclass, "oneaxis",   siren_prim_oneaxis,   ARGS_NONE());
  mrb_define_class_method(mrb, rclass, "prism",     siren_prim_prism,     ARGS_NONE());
  mrb_define_class_method(mrb, rclass, "revol",     siren_prim_revol,     ARGS_NONE());
  mrb_define_class_method(mrb, rclass, "revolution",siren_prim_revolution,ARGS_NONE());
  mrb_define_class_method(mrb, rclass, "sweep",     siren_prim_sweep,     ARGS_NONE());
  mrb_define_class_method(mrb, rclass, "wedge",     siren_prim_wedge,     ARGS_NONE());
  return true;
}

mrb_value siren_prim_box(mrb_state* mrb, mrb_value self)
{
  mrb_value size, pos;
  int argc = mrb_get_args(mrb, "o|o", &size, &pos);

  gp_Vec* vsize = siren_vec_get(mrb, size);
  Standard_Real sx = vsize->X();
  Standard_Real sy = vsize->Y();
  Standard_Real sz = vsize->Z();

  gp_Pnt op;
  if (argc == 2) {
    op = siren_pnt_get(mrb, pos);
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
    op = siren_pnt_get(mrb, pos);
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

  gp_Ax2 ax = siren_ax2s_get(mrb, pos, norm);

  BRepPrimAPI_MakeCylinder api(ax, (Standard_Real)r, (Standard_Real)h, (Standard_Real)a);

  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_cone(mrb_state* mrb, mrb_value self)
{
  mrb_value pos, norm;
  mrb_float r1, r2, h, ang;
  int argc = mrb_get_args(mrb, "ooffff", &pos, &norm, &r1, &r2, &h, &ang);

  gp_Ax2 ax = siren_ax2s_get(mrb, pos, norm);

  BRepPrimAPI_MakeCone api(ax, (Standard_Real)r1, (Standard_Real)r2, (Standard_Real)h, (Standard_Real)ang);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_torus(mrb_state* mrb, mrb_value self)
{
  mrb_float r1, r2, ang;
  mrb_value pos, norm;
  int argc = mrb_get_args(mrb, "oofff", &pos, &norm, &r1, &r2, &ang);

  gp_Ax2 ax = siren_ax2s_get(mrb, pos, norm);

  BRepPrimAPI_MakeTorus api(ax, (Standard_Real)r1, (Standard_Real)r2, (Standard_Real)ang);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_prim_halfspace(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_prim_oneaxis(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_prim_prism(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_prim_revol(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_prim_revolution(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_prim_sweep(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_prim_wedge(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

