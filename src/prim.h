#ifndef _PRIM_H_
#define _PRIM_H_

#include "siren.h"

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>

bool siren_prim_install(mrb_state* mrb, struct RClass* rclass);

mrb_value siren_prim_box        (mrb_state* mrb, mrb_value self);
mrb_value siren_prim_sphere     (mrb_state* mrb, mrb_value self);
mrb_value siren_prim_cylinder   (mrb_state* mrb, mrb_value self);
mrb_value siren_prim_cone       (mrb_state* mrb, mrb_value self);
mrb_value siren_prim_torus      (mrb_state* mrb, mrb_value self);
mrb_value siren_prim_halfspace  (mrb_state* mrb, mrb_value self);
mrb_value siren_prim_oneaxis    (mrb_state* mrb, mrb_value self);
mrb_value siren_prim_prism      (mrb_state* mrb, mrb_value self);
mrb_value siren_prim_revol      (mrb_state* mrb, mrb_value self);
mrb_value siren_prim_revolution (mrb_state* mrb, mrb_value self);
mrb_value siren_prim_sweep      (mrb_state* mrb, mrb_value self);
mrb_value siren_prim_wedge      (mrb_state* mrb, mrb_value self);

#endif
