#include "proj.h"

bool siren_proj_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Proj");
  mrb_define_class_method(mrb, rclass, "wire", siren_proj_wire, ARGS_REQ(3));
  return true;
}

mrb_value siren_proj_wire(mrb_state* mrb, mrb_value self)
{
  mrb_value w, f, v;
  int argc = mrb_get_args(mrb, "ooo", &w, &f, &v);

  TopoDS_Shape* wire = siren_shape_get(mrb, w);
  TopoDS_Shape* face = siren_shape_get(mrb, f);

  gp_Vec* vec = siren_vec_get(mrb, v);

  BRepProj_Projection bpp(*wire, *face, *vec);
  TopoDS_Shape* shape = siren_occ_shape_new(mrb);
  *shape = bpp.Shape();

  return siren_shape_new(mrb, shape);
}

