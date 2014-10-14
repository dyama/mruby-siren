#include "loc.h"

TopLoc_Location* siren_loc_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<TopLoc_Location*>(mrb_get_datatype(mrb, obj, &siren_loc_type));
}

bool siren_loc_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Loc", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", siren_loc_init, ARGS_NONE());
  return true;
}

mrb_value siren_loc_init(mrb_state* mrb, mrb_value self)
{
  void* p = mrb_malloc(mrb, sizeof(TopLoc_Location));
  TopLoc_Location* loc = new(p) TopLoc_Location();
  DATA_PTR(self) = loc;
  DATA_TYPE(self) = &siren_loc_type;
  return self;
}

void siren_loc_final(mrb_state* mrb, void* p)
{
  TopLoc_Location* t = static_cast<TopLoc_Location*>(p);
  mrb_free(mrb, t);
}

