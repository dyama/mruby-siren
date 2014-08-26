#include "exp.h"

bool siren_exp_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Exp", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", siren_exp_init, ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "to_a",       siren_exp_to_a, ARGS_NONE());

  mrb_define_method(mrb, rclass, "init",       siren_exp_init2,    ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "reinit",     siren_exp_reinit,   ARGS_NONE());
  mrb_define_method(mrb, rclass, "depth",      siren_exp_depth,    ARGS_NONE());
  mrb_define_method(mrb, rclass, "clear",      siren_exp_clear,    ARGS_NONE());
  mrb_define_method(mrb, rclass, "more",       siren_exp_more,     ARGS_NONE());
  mrb_define_method(mrb, rclass, "next",       siren_exp_next,     ARGS_NONE());
  mrb_define_method(mrb, rclass, "current",     siren_exp_current, ARGS_NONE());

  return true;
}

mrb_value siren_exp_init(mrb_state* mrb, mrb_value self)
{
  mrb_value obj;
  mrb_int type;
  int argc = mrb_get_args(mrb, "oi", &obj, &type);

  TopoDS_Shape* shape = siren_shape_get(mrb, obj);
  TopExp_Explorer* exp = new TopExp_Explorer(*shape, (TopAbs_ShapeEnum)type);

  DATA_PTR(self) = exp;
  DATA_TYPE(self) = &siren_exp_type;
  return self;
}

void siren_exp_final(mrb_state* mrb, void* p)
{
  TopExp_Explorer* exp = static_cast<TopExp_Explorer*>(p);
  delete exp;
}

mrb_value siren_exp_to_a(mrb_state* mrb, mrb_value self)
{
  TopExp_Explorer* exp = siren_exp_get(mrb, self);
  mrb_value res = mrb_ary_new(mrb);

  for (exp->ReInit(); exp->More(); exp->Next()) {
    TopoDS_Shape* s = new TopoDS_Shape();
    *s = exp->Current();
    mrb_value item = siren_shape_new(mrb, s);
    mrb_ary_push(mrb, res, item);
  }

  return res;
}

mrb_value siren_exp_init2(mrb_state* mrb, mrb_value self)
{
  mrb_value obj;
  mrb_int type;
  int argc = mrb_get_args(mrb, "oi", &obj, &type);

  TopoDS_Shape* shape = siren_shape_get(mrb, obj);
  TopExp_Explorer* exp = siren_exp_get(mrb, self);
  exp->Init(*shape, (TopAbs_ShapeEnum)type);

  return mrb_nil_value();
}

mrb_value siren_exp_reinit(mrb_state* mrb, mrb_value self)
{
  TopExp_Explorer* exp = siren_exp_get(mrb, self);
  exp->ReInit();
  return mrb_nil_value();
}

mrb_value siren_exp_depth(mrb_state* mrb, mrb_value self)
{
  TopExp_Explorer* exp = siren_exp_get(mrb, self);
  Standard_Integer n = exp->Depth();
  return mrb_fixnum_value(n);
}

mrb_value siren_exp_clear(mrb_state* mrb, mrb_value self)
{
  TopExp_Explorer* exp = siren_exp_get(mrb, self);
  exp->Clear();
  return mrb_nil_value();
}

mrb_value siren_exp_more(mrb_state* mrb, mrb_value self)
{
  TopExp_Explorer* exp = siren_exp_get(mrb, self);
  Standard_Boolean res = exp->More();
  return res ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_exp_next(mrb_state* mrb, mrb_value self)
{
  TopExp_Explorer* exp = siren_exp_get(mrb, self);
  exp->Next();
  return mrb_nil_value();
}

mrb_value siren_exp_current(mrb_state* mrb, mrb_value self)
{
  TopExp_Explorer* exp = siren_exp_get(mrb, self);
  TopoDS_Shape* s = new TopoDS_Shape();
  *s = exp->Current();
  return siren_shape_new(mrb, s);
}

TopExp_Explorer* siren_exp_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<TopExp_Explorer*>(mrb_get_datatype(mrb, obj, &siren_exp_type));
}

