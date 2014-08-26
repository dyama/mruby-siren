#include "exp.h"

bool mrb_siren_exp_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Exp", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", mrb_method_name(exp_init), ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "to_a",       mrb_method_name(exp_to_a), ARGS_NONE());

  mrb_define_method(mrb, rclass, "init",       mrb_method_name(exp_init2),    ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "reinit",     mrb_method_name(exp_reinit),   ARGS_NONE());
  mrb_define_method(mrb, rclass, "depth",      mrb_method_name(exp_depth),    ARGS_NONE());
  mrb_define_method(mrb, rclass, "clear",      mrb_method_name(exp_clear),    ARGS_NONE());
  mrb_define_method(mrb, rclass, "more",       mrb_method_name(exp_more),     ARGS_NONE());
  mrb_define_method(mrb, rclass, "next",       mrb_method_name(exp_next),     ARGS_NONE());
  mrb_define_method(mrb, rclass, "current",     mrb_method_name(exp_current), ARGS_NONE());

  return true;
}

mrb_method(exp_init)
{
  mrb_value obj;
  mrb_int type;
  int argc = mrb_get_args(mrb, "oi", &obj, &type);

  TopoDS_Shape* shape = mrb_siren_get_shape(mrb, obj);
  TopExp_Explorer* exp = new TopExp_Explorer(*shape, (TopAbs_ShapeEnum)type);

  DATA_PTR(self) = exp;
  DATA_TYPE(self) = &mrb_siren_exp_type;
  return self;
}

void mrb_siren_exp_final(mrb_state* mrb, void* p)
{
  TopExp_Explorer* exp = static_cast<TopExp_Explorer*>(p);
  delete exp;
}

mrb_method(exp_to_a)
{
  TopExp_Explorer* exp = mrb_siren_get_exp(mrb, self);
  mrb_value res = mrb_ary_new(mrb);

  for (exp->ReInit(); exp->More(); exp->Next()) {
    TopoDS_Shape* s = new TopoDS_Shape();
    *s = exp->Current();
    mrb_value item = mrb_siren_shape_new(mrb, s);
    mrb_ary_push(mrb, res, item);
  }

  return res;
}

mrb_method(exp_init2)
{
  mrb_value obj;
  mrb_int type;
  int argc = mrb_get_args(mrb, "oi", &obj, &type);

  TopoDS_Shape* shape = mrb_siren_get_shape(mrb, obj);
  TopExp_Explorer* exp = mrb_siren_get_exp(mrb, self);
  exp->Init(*shape, (TopAbs_ShapeEnum)type);

  return mrb_nil_value();
}

mrb_method(exp_reinit)
{
  TopExp_Explorer* exp = mrb_siren_get_exp(mrb, self);
  exp->ReInit();
  return mrb_nil_value();
}

mrb_method(exp_depth)
{
  TopExp_Explorer* exp = mrb_siren_get_exp(mrb, self);
  Standard_Integer n = exp->Depth();
  return mrb_fixnum_value(n);
}

mrb_method(exp_clear)
{
  TopExp_Explorer* exp = mrb_siren_get_exp(mrb, self);
  exp->Clear();
  return mrb_nil_value();
}

mrb_method(exp_more)
{
  TopExp_Explorer* exp = mrb_siren_get_exp(mrb, self);
  Standard_Boolean res = exp->More();
  return res ? mrb_true_value() : mrb_false_value();
}

mrb_method(exp_next)
{
  TopExp_Explorer* exp = mrb_siren_get_exp(mrb, self);
  exp->Next();
  return mrb_nil_value();
}

mrb_method(exp_current)
{
  TopExp_Explorer* exp = mrb_siren_get_exp(mrb, self);
  TopoDS_Shape* s = new TopoDS_Shape();
  *s = exp->Current();
  return mrb_siren_shape_new(mrb, s);
}

TopExp_Explorer* mrb_siren_get_exp(mrb_state* mrb, mrb_value obj)
{
  return static_cast<TopExp_Explorer*>(mrb_get_datatype(mrb, obj, &mrb_siren_exp_type));
}

