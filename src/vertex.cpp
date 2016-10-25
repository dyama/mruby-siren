#include "shape/vertex.h"

void siren_vertex_install(mrb_state* mrb, RObject* o)
{
  mrb_define_singleton_method(mrb, o, "xyz",  siren_vertex_xyz, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "to_a", siren_vertex_xyz, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, o, "to_v", siren_vertex_to_v, MRB_ARGS_NONE());
  return;
}

mrb_value siren_vertex_xyz(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  TopoDS_Vertex vertex = TopoDS::Vertex(*shape);
  return siren_pnt_to_ary(mrb, BRep_Tool::Pnt(vertex));
}

mrb_value siren_vertex_to_v(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  TopoDS_Vertex vertex = TopoDS::Vertex(*shape);
  gp_Pnt p =BRep_Tool::Pnt(vertex);
  return siren_vec_new(mrb, p.X(), p.Y(), p.Z());
}
