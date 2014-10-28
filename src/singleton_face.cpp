#include "singleton_face.h"

void siren_face_install(mrb_state* mrb, RObject* o)
{
  mrb_define_singleton_method(mrb, o, "normal", siren_face_normal, MRB_ARGS_NONE());
  return;
}

mrb_value siren_face_normal(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* c = siren_shape_get(mrb, self);
  TopoDS_Face f = TopoDS::Face(*c);
  Standard_Real umin, umax, vmin, vmax;
  BRepTools::UVBounds(f, umin, umax, vmin, vmax);
  Handle(Geom_Surface) gsurf = BRep_Tool::Surface(f);
  GeomLProp_SLProps props(gsurf, umin, vmin, 1, 0.01);
  gp_Dir n = props.Normal();
  return siren_vec_new(mrb, n.X(), n.Y(), n.Z());
}

