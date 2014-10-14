#include "loc.h"

TopLoc_Location* siren_loc_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<TopLoc_Location*>(mrb_get_datatype(mrb, obj, &siren_loc_type));
}

bool siren_loc_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Loc", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize",  siren_loc_init,        ARGS_NONE());
  mrb_define_method(mrb, rclass, "identity?",   siren_loc_is_identity, ARGS_NONE());
  mrb_define_method(mrb, rclass, "identity",    siren_loc_identity,    ARGS_NONE());
  mrb_define_method(mrb, rclass, "first_datum", siren_loc_first_datum, ARGS_NONE());
  mrb_define_method(mrb, rclass, "first_power", siren_loc_first_power, ARGS_NONE());
  mrb_define_method(mrb, rclass, "next",        siren_loc_next,        ARGS_NONE());
  mrb_define_method(mrb, rclass, "trans",       siren_loc_trans,       ARGS_NONE());
  mrb_define_method(mrb, rclass, "inverted",    siren_loc_inverted,    ARGS_NONE());
  mrb_define_method(mrb, rclass, "multiplied",  siren_loc_multiplied,  ARGS_NONE());
  // mrb_define_method(mrb, rclass, "*",           siren_loc_multiplied,  ARGS_NONE());
  mrb_define_method(mrb, rclass, "divided",     siren_loc_divided,     ARGS_NONE());
  // mrb_define_method(mrb, rclass, "/",           siren_loc_divided,     ARGS_NONE());
  mrb_define_method(mrb, rclass, "predivided",  siren_loc_predivided,  ARGS_NONE());
  mrb_define_method(mrb, rclass, "powered",     siren_loc_powered,     ARGS_NONE());
  mrb_define_method(mrb, rclass, "hashcode",    siren_loc_hashcode,    ARGS_NONE());
  mrb_define_method(mrb, rclass, "equal?",      siren_loc_is_equal,    ARGS_NONE());
  // mrb_define_method(mrb, rclass, "==",      siren_loc_is_equal,    ARGS_NONE());
  mrb_define_method(mrb, rclass, "dump",       siren_loc_is_dump,      ARGS_NONE());
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

mrb_value siren_loc_is_identity(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_loc_identity(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_loc_first_datum(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_loc_first_power(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_loc_next(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_loc_trans(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_loc_inverted(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_loc_multiplied(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_loc_divided(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_loc_predivided(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_loc_powered(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_loc_hashcode(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_loc_is_equal(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

mrb_value siren_loc_is_dump(mrb_state* mrb, mrb_value self)
{
  return mrb_exc_new(mrb, E_NOTIMP_ERROR, NULL, 0);
}

