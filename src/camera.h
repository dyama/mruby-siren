#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "siren.h"
#include "world.h"

#include <Aspect_Handle.hxx>
#include <V3d_View.hxx>
#include <V3d_PerspectiveView.hxx>

#ifdef _WNT
// for Microsoft Windows
#include <WNT_Window.hxx>
#else
// for UNIX compatible system (X-Window System)
#include <Xw_Window.hxx>
#endif

void siren_camera_final(mrb_state* mrb, void* p);
bool siren_camera_install(mrb_state* mrb, struct RClass* rclass);
static struct mrb_data_type siren_camera_type = { "Camera", siren_camera_final };
Handle(V3d_View) siren_camera_get(mrb_state* mrb, mrb_value obj);

mrb_value siren_camera_init(mrb_state* mrb, mrb_value self);

mrb_value siren_camera_fit(mrb_state* mrb, mrb_value self);
mrb_value siren_camera_fitz(mrb_state* mrb, mrb_value self);

mrb_value siren_camera_set_proj(mrb_state* mrb, mrb_value self);

#endif
