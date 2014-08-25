#include "exp.h"

mrb_data_type* mrb_siren_get_exp_type(void)
{
  return &mrb_siren_exp_type;
}

bool mrb_siren_exp_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Exp", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", mrb_method_name(exp_init), ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "to_a",       mrb_method_name(exp_to_a), ARGS_NONE());
  return true;
}

mrb_method(exp_init)
{
  mrb_value obj;
  mrb_int type;
  int argc = mrb_get_args(mrb, "oi", &obj, &type);

  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, obj, mrb_siren_get_shape_type()));
  TopExp_Explorer* exp = new TopExp_Explorer(*shape, (TopAbs_ShapeEnum)type);

  DATA_PTR(self) = exp;
  DATA_TYPE(self) = mrb_siren_get_exp_type();
  return self;
}

void mrb_siren_exp_final(mrb_state* mrb, void* p)
{
  TopExp_Explorer* exp = static_cast<TopExp_Explorer*>(p);
  delete exp;
}

mrb_method(exp_to_a)
{
  TopExp_Explorer* exp = static_cast<TopExp_Explorer*>(mrb_get_datatype(mrb, self, mrb_siren_get_exp_type()));

  mrb_value res = mrb_ary_new(mrb);

  for (; exp->More(); exp->Next()) {
    TopoDS_Shape* s = new TopoDS_Shape();
    *s = exp->Current();
    mrb_value item = mrb_siren_shape_new(mrb, s);
    mrb_ary_push(mrb, res, item);
  }

  return res;
}

