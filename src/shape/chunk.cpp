#ifdef SIREN_ENABLE_CHUNK

#include "shape/chunk.h"

mrb_value siren_chunk_new(mrb_state* mrb, const TopoDS_Shape* src)
{
  mrb_value obj;
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Chunk")));
  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = *src; // Copy to inner native member
  DATA_PTR(obj)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(obj) = &siren_chunk_type;
  return obj;
}

TopoDS_CompSolid siren_chunk_get(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, self, &siren_chunk_type));
  TopoDS_CompSolid chunk = TopoDS::CompSolid(*shape);
  if (chunk.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Chunk."); }
  return chunk;
}

bool siren_chunk_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* cls_chunk = mrb_define_class_under(mrb, mod_siren, "Chunk", cls_shape);
  MRB_SET_INSTANCE_TT(cls_chunk, MRB_TT_DATA);
  mrb_define_method(mrb, cls_chunk, "initialize", siren_chunk_init,   MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_chunk, "to_solid",  siren_chunk_to_solid, MRB_ARGS_NONE());
  return true;
}

struct RClass* siren_chunk_rclass(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Chunk")));
}

mrb_value siren_chunk_obj(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Chunk"));
}

mrb_value siren_chunk_init(mrb_state* mrb, mrb_value self)
{
  mrb_value* a;
  mrb_int len;
  int argc = mrb_get_args(mrb, "*", &a, &len);

  TopoDS_CompSolid cs;
  TopoDS_Builder builder;
  builder.MakeCompSolid(cs);

  for (int i = 0; i < len; i++) {
    if (mrb_array_p(a[i])) {
      for (int j = 0; j < mrb_ary_len(mrb, a[i]); j++) {
        auto solid = siren_solid_get(mrb, mrb_ary_ref(mrb, a[i], j));
        builder.Add(cs, solid);
      }
    }
    else {
      auto solid = siren_solid_get(mrb, a[i]);
      builder.Add(cs, solid);
    }
  }

  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = cs; // Copy to inner native member
  DATA_PTR(self)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(self) = &siren_chunk_type;
  return self;
}

mrb_value siren_chunk_to_solid(mrb_state* mrb, mrb_value self)
{
  auto cs = siren_chunk_get(mrb, self);
  auto solid = BRepBuilderAPI_MakeSolid(cs);
  return siren_shape_new(mrb, solid);
}

#endif
