#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "siren.h"

void mrb_siren_shape_final(mrb_state* mrb, void* p);
bool mrb_siren_shape_install(mrb_state* mrb, struct RClass* rclass);
static struct mrb_data_type mrb_siren_shape_type = { "Shape", mrb_siren_shape_final };
mrb_data_type* mrb_siren_get_shape_type(void);

mrb_method(shape_init);
mrb_method(shape_to_s);
mrb_method(shape_is_null);
mrb_method(shape_shapetype);

#endif
