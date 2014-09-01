#include "offset.h"

bool siren_offset_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_module(mrb, "Offset");
  mrb_define_class_method(mrb, rclass, "sweep_vec", siren_offset_sweep_vec, ARGS_REQ(2));
  return true;
}

mrb_value siren_offset_sweep_vec(mrb_state* mrb, mrb_value self)
{
  mrb_value target, vec;
  int argc = mrb_get_args(mrb, "oA", &target, &vec);

  TopoDS_Shape* profile = siren_shape_get(mrb, target);

  gp_Vec* _vec = siren_vec_get(mrb, vec);
  gp_Pnt _pt = gp_Pnt(0., 0., 0.).Transformed(profile->Location());

  TopoDS_Edge pe = BRepBuilderAPI_MakeEdge(_pt, gp_Pnt(_vec->X(), _vec->Y(), _vec->Z()));
  TopoDS_Wire path = BRepBuilderAPI_MakeWire(pe);

  BRepOffsetAPI_MakePipe mp(path, *profile);
  mp.Build();

  TopoDS_Shape* shape = new TopoDS_Shape();
  *shape = mp.Shape();

  return siren_shape_new(mrb, shape);
}

