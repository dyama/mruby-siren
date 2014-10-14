#ifndef _LOC_H_
#define _LOC_H_

#include "common.h"
#include "siren.h"
#include "vec.h"

#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax3.hxx>
#include <gp_Trsf.hxx>

#include <TopLoc_Location.hxx>

bool siren_loc_install(mrb_state* mrb, struct RClass* rclass);
void siren_loc_final(mrb_state* mrb, void* p);
static struct mrb_data_type siren_loc_type = { "Loc", siren_loc_final };
TopLoc_Location* siren_loc_get(mrb_state* mrb, mrb_value obj);

mrb_value siren_loc_init(mrb_state* mrb, mrb_value self);

#endif
