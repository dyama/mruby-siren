#include "vertex.h"

void siren_vertex_install(mrb_state* mrb, RObject* o)
{
  mrb_define_singleton_method(mrb, o, "xyz", siren_vertex_xyz, MRB_ARGS_NONE());
  return;
}

mrb_value siren_vertex_xyz(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  TopoDS_Vertex vertex = TopoDS::Vertex(*shape);
  return siren_pnt_to_ary(mrb, BRep_Tool::Pnt(vertex));
}

