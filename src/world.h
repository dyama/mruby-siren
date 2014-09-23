#ifndef _WORLD_H_
#define _WORLD_H_

#include "siren.h"

void siren_world_final(mrb_state* mrb, void* p);
bool siren_world_install(mrb_state* mrb, struct RClass* rclass);
static struct mrb_data_type siren_world_type = { "World", siren_world_final };

mrb_value siren_world_init(mrb_state* mrb, mrb_value self);

#endif
