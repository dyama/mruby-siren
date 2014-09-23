#include "world.h"

bool siren_world_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "World", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", siren_world_init,       ARGS_NONE());

  return true;
}

mrb_value siren_world_init(mrb_state* mrb, mrb_value self)
{
  return mrb_nil_value();
}

void siren_world_final(mrb_state* mrb, void* p)
{
  // TopoDS_world* s = static_cast<TopoDS_world*>(p);
  // s->Nullify();
  // mrb_free(mrb, s);
}

