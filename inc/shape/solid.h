#ifndef _SHAPE_SOLID_H_
#define _SHAPE_SOLID_H_

#include "siren.h"

#include <TopoDS.hxx>
#include <TopoDS_Solid.hxx>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeHalfSpace.hxx>
#include <BRepPrimAPI_MakeWedge.hxx>

static struct mrb_data_type siren_solid_type = { "Solid", siren_shape_final };
bool siren_solid_install(mrb_state* mrb, struct RClass* mod_siren);
TopoDS_Solid siren_solid_get(mrb_state* mrb, mrb_value self);
mrb_value siren_solid_new(mrb_state* mrb, const TopoDS_Shape* src);
mrb_value siren_solid_obj(mrb_state* mrb);
struct RClass* siren_solid_rclass(mrb_state* mrb);

mrb_value siren_solid_init(mrb_state* mrb, mrb_value self);

mrb_value siren_solid_box        (mrb_state* mrb, mrb_value self);
mrb_value siren_solid_box2p      (mrb_state* mrb, mrb_value self);
mrb_value siren_solid_boxax      (mrb_state* mrb, mrb_value self);
mrb_value siren_solid_sphere     (mrb_state* mrb, mrb_value self);
mrb_value siren_solid_cylinder   (mrb_state* mrb, mrb_value self);
mrb_value siren_solid_cone       (mrb_state* mrb, mrb_value self);
mrb_value siren_solid_torus      (mrb_state* mrb, mrb_value self);
mrb_value siren_solid_halfspace  (mrb_state* mrb, mrb_value self);
mrb_value siren_solid_prism      (mrb_state* mrb, mrb_value self);
mrb_value siren_solid_revol      (mrb_state* mrb, mrb_value self);
mrb_value siren_solid_revolution (mrb_state* mrb, mrb_value self);
mrb_value siren_solid_wedge      (mrb_state* mrb, mrb_value self);

#endif
