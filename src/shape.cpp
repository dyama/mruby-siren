#include "shape.h"

mrb_value siren_shape_new(mrb_state* mrb, const TopoDS_Shape& shape)
{
  mrb_value obj;
  obj = mrb_instance_alloc(mrb, mrb_obj_value(mrb_class_get(mrb, "Shape")));
  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = shape; // Copy to inner native member
  DATA_PTR(obj)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(obj) = &siren_shape_type;
  return obj;
}

bool siren_shape_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Shape", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize", siren_shape_init,       ARGS_NONE());
  mrb_define_method(mrb, rclass, "inspect",    siren_shape_to_s,       ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_s",       siren_shape_to_s,       ARGS_NONE());
  mrb_define_method(mrb, rclass, "null?",      siren_shape_is_null,    ARGS_NONE());
  mrb_define_method(mrb, rclass, "shapetype",  siren_shape_shapetype,  ARGS_NONE());
  mrb_define_method(mrb, rclass, "location",   siren_shape_location,   ARGS_NONE());
  mrb_define_method(mrb, rclass, "bndbox",     siren_shape_bndbox,     ARGS_NONE());

  mrb_define_method(mrb, rclass, "translate!", siren_shape_translate_bang, ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "rotate!",    siren_shape_rotate_bang,    ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "scale!",     siren_shape_scale_bang,     ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "mirror!",    siren_shape_mirror_bang,    ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "move!",      siren_shape_move_bang,      ARGS_REQ(1));

  mrb_define_method(mrb, rclass, "translate",  siren_shape_translate,  ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "rotate",     siren_shape_rotate,     ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "scale",      siren_shape_scale,      ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "mirror",     siren_shape_mirror,     ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "move",       siren_shape_move,       ARGS_REQ(1));

  mrb_define_method(mrb, rclass, "hashcode",   siren_shape_hashcode,   ARGS_NONE());

  mrb_define_method(mrb, rclass, "partner?",   siren_shape_is_partner, ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "same?",      siren_shape_is_same,    ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "equal?",     siren_shape_is_equal,   ARGS_REQ(1));

  mrb_define_method(mrb, rclass, "explore",    siren_shape_explore,    ARGS_REQ(1));

  return true;
}

mrb_value siren_shape_init(mrb_state* mrb, mrb_value self)
{
  mrb_raise(mrb, E_NOMETHOD_ERROR, "private method `new' called for Shape:Class");
}

void siren_shape_final(mrb_state* mrb, void* p)
{
  TopoDS_Shape* s = static_cast<TopoDS_Shape*>(p);
  s->Nullify();
  mrb_free(mrb, s);
}

mrb_value siren_shape_to_s(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  RClass* krass = mrb_module_get(mrb, "ShapeType");
  mrb_value shapetype = mrb_funcall(mrb, mrb_obj_value(krass), "to_s", 1, mrb_fixnum_value((int)shape->ShapeType()));
  mrb_value str = mrb_str_new_cstr(mrb, "#Shape<@shapetype=");
  mrb_str_append(mrb, str, shapetype);
  mrb_str_append(mrb, str, mrb_str_new_cstr(mrb, ">"));
  return str;
}

mrb_value siren_shape_is_null(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  return shape->IsNull() ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_shape_shapetype(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  int type = (int)shape->ShapeType();
  return mrb_fixnum_value(type);
}

mrb_value siren_shape_location(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  gp_XYZ pos = shape->Location().Transformation().TranslationPart();
  return siren_vec_new(mrb, pos.X(), pos.Y(), pos.Z());
}

mrb_value siren_shape_bndbox(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  return siren_bndbox_new(mrb, *shape);
}

TopoDS_Shape* siren_shape_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, obj, &siren_shape_type));
}

mrb_value siren_shape_translate_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value vec;
  int argc = mrb_get_args(mrb, "o", &vec);
  gp_Trsf trsf;
  trsf.SetTranslation(*siren_vec_get(mrb, vec));
  siren_shape_get(mrb, self)->Move(trsf);
  return mrb_nil_value();
}

mrb_value siren_shape_rotate_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  mrb_float ang;
  int argc = mrb_get_args(mrb, "oof", &op, &norm, &ang);
  gp_Trsf trsf;
  trsf.SetRotation(siren_ax1_get(mrb, op, norm), (Standard_Real)ang);
  siren_shape_get(mrb, self)->Move(trsf);
  return mrb_nil_value();
}

mrb_value siren_shape_scale_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op;
  mrb_float factor;
  int argc = mrb_get_args(mrb, "of", &op, &factor);
  gp_Trsf trsf;
  trsf.SetScale(siren_pnt_get(mrb, op), (Standard_Real)factor);
  siren_shape_get(mrb, self)->Move(trsf);
  return mrb_nil_value();
}

mrb_value siren_shape_mirror_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  int argc = mrb_get_args(mrb, "oo", &op, &norm);
  gp_Trsf trsf;
  trsf.SetMirror(siren_ax2s_get(mrb, op, norm));
  siren_shape_get(mrb, self)->Move(trsf);
  return mrb_nil_value();
}

mrb_value siren_shape_move_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value trans;
  int argc = mrb_get_args(mrb, "o", &trans);
  gp_Trsf* t = siren_trans_get(mrb, trans);
  siren_shape_get(mrb, self)->Move(*t);
  return mrb_nil_value();
}

mrb_value siren_shape_translate(mrb_state* mrb, mrb_value self)
{
  mrb_value vec;
  int argc = mrb_get_args(mrb, "o", &vec);
  gp_Trsf trsf;
  trsf.SetTranslation(*siren_vec_get(mrb, vec));
  return siren_shape_new(mrb, siren_shape_get(mrb, self)->Moved(trsf));
}

mrb_value siren_shape_rotate(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  mrb_float ang;
  int argc = mrb_get_args(mrb, "oof", &op, &norm, &ang);
  gp_Trsf trsf;
  trsf.SetRotation(siren_ax1_get(mrb, op, norm), (Standard_Real)ang);
  return siren_shape_new(mrb, siren_shape_get(mrb, self)->Moved(trsf));
}

mrb_value siren_shape_scale(mrb_state* mrb, mrb_value self)
{
  mrb_value op;
  mrb_float factor;
  int argc = mrb_get_args(mrb, "of", &op, &factor);
  gp_Trsf trsf;
  trsf.SetScale(siren_pnt_get(mrb, op), (Standard_Real)factor);
  return siren_shape_new(mrb, siren_shape_get(mrb, self)->Moved(trsf));
}

mrb_value siren_shape_mirror(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  int argc = mrb_get_args(mrb, "oo", &op, &norm);
  gp_Trsf trsf;
  trsf.SetMirror(siren_ax2s_get(mrb, op, norm));
  return siren_shape_new(mrb, siren_shape_get(mrb, self)->Moved(trsf));
}

mrb_value siren_shape_move(mrb_state* mrb, mrb_value self)
{
  mrb_value trans;
  int argc = mrb_get_args(mrb, "o", &trans);
  gp_Trsf* t = siren_trans_get(mrb, trans);
  return siren_shape_new(mrb, siren_shape_get(mrb, self)->Moved(*t));
}

mrb_value siren_shape_hashcode(mrb_state* mrb, mrb_value self)
{
  mrb_int upper;
  int argc = mrb_get_args(mrb, "i", &upper);
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  return mrb_fixnum_value(shape->HashCode(upper));
}

mrb_value siren_shape_is_partner(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  TopoDS_Shape* shape_self  = siren_shape_get(mrb, self);
  TopoDS_Shape* shape_other = siren_shape_get(mrb, other);
  return shape_self->IsPartner(*shape_other) ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_shape_is_same(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  TopoDS_Shape* shape_self  = siren_shape_get(mrb, self);
  TopoDS_Shape* shape_other = siren_shape_get(mrb, other);
  return shape_self->IsSame(*shape_other) ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_shape_is_equal(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  TopoDS_Shape* shape_self  = siren_shape_get(mrb, self);
  TopoDS_Shape* shape_other = siren_shape_get(mrb, other);
  return shape_self->IsEqual(*shape_other) ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_shape_explore(mrb_state* mrb, mrb_value self)
{
  mrb_int type;
  mrb_value block;
  int argc = mrb_get_args(mrb, "i&", &type, &block);
  TopExp_Explorer ex(*siren_shape_get(mrb, self), (TopAbs_ShapeEnum)type);
  if (!mrb_nil_p(block)) {
    for (; ex.More(); ex.Next()) {
      mrb_value argv[2];
      argv[0] = siren_shape_new(mrb, ex.Current());
      argv[1] = mrb_fixnum_value(ex.Depth());
      mrb_yield_argv(mrb, block, 2, argv);
    }
    return self;
  }
  mrb_value ar = mrb_ary_new(mrb);
  for (; ex.More(); ex.Next()) {
    mrb_int ai = mrb_gc_arena_save(mrb);
    mrb_ary_push(mrb, ar, siren_shape_new(mrb, ex.Current()));
    mrb_gc_arena_restore(mrb, ai);
  }
  return ar;
}

