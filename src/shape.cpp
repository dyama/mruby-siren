/*
 * Document-class: Shape
 *
 */

#include "shape.h"

TopoDS_Shape* siren_shape_get(mrb_state* mrb, mrb_value obj)
{
  // return static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, obj, &siren_shape_type));
  // Get ptr without type checking.
  return static_cast<TopoDS_Shape*>(DATA_PTR(obj));
}

mrb_value siren_shape_new(mrb_state* mrb, const TopoDS_Shape& shape)
{
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  switch (shape.ShapeType()) {
    case TopAbs_VERTEX:    return siren_vertex_new(mrb, &shape);   break;
    case TopAbs_EDGE:      return siren_edge_new(mrb, &shape);     break;
    case TopAbs_WIRE:      return siren_wire_new(mrb, &shape);     break;
    case TopAbs_FACE:      return siren_face_new(mrb, &shape);     break;
    case TopAbs_SHELL:     return siren_shell_new(mrb, &shape);    break;
    case TopAbs_SOLID:     return siren_solid_new(mrb, &shape);    break;
#ifdef SIREN_ENABLE_CHUNK
    case TopAbs_COMPSOLID: return siren_chunk_new(mrb, &shape);    break;
#endif
    case TopAbs_COMPOUND:  return siren_compound_new(mrb, &shape); break;
    default: break;
  }
  mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make Shape object.");
  return mrb_nil_value();
}

struct RClass* siren_shape_rclass(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Shape")));
}

bool siren_shape_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_shape = mrb_define_class_under(mrb, mod_siren, "Shape", mrb->object_class);
  MRB_SET_INSTANCE_TT(cls_shape, MRB_TT_DATA);
  mrb_define_method(mrb, cls_shape, "initialize", siren_shape_init,       MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "null?",      siren_shape_is_null,    MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "pos",        siren_shape_pos,        MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "trans",      siren_shape_trans,      MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "trans=",     siren_shape_set_trans,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_shape, "bndbox",     siren_shape_bndbox,     MRB_ARGS_NONE());

  mrb_define_method(mrb, cls_shape, "translate!", siren_shape_translate_bang, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_shape, "rotate!",    siren_shape_rotate_bang,    MRB_ARGS_REQ(3));
  mrb_define_method(mrb, cls_shape, "scale!",     siren_shape_scale_bang,     MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_shape, "mirror!",    siren_shape_mirror_bang,    MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_shape, "move!",      siren_shape_move_bang,      MRB_ARGS_REQ(1));

  mrb_define_method(mrb, cls_shape, "translate",  siren_shape_translate,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_shape, "rotate",     siren_shape_rotate,     MRB_ARGS_REQ(3));
  mrb_define_method(mrb, cls_shape, "scale",      siren_shape_scale,      MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_shape, "mirror",     siren_shape_mirror,     MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_shape, "move",       siren_shape_move,       MRB_ARGS_REQ(1));

  mrb_define_method(mrb, cls_shape, "hashcode",   siren_shape_hashcode,   MRB_ARGS_NONE());

  mrb_define_method(mrb, cls_shape, "partner?",   siren_shape_is_partner, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_shape, "same?",      siren_shape_is_same,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_shape, "equal?",     siren_shape_is_equal,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_shape, "<=>",        siren_shape_is_equal,   MRB_ARGS_REQ(1));

  mrb_define_method(mrb, cls_shape, "explore",    siren_shape_explore,    MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_method(mrb, cls_shape, "subshapes",  siren_shape_subshapes,  MRB_ARGS_OPT(2));

  mrb_define_method(mrb, cls_shape, "section",    siren_shape_section,    MRB_ARGS_REQ(1));

  mrb_define_method(mrb, cls_shape, "reverse",    siren_shape_reverse,     MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "reverse!",   siren_shape_reverse_bang,MRB_ARGS_NONE());

#ifdef SIREN_ENABLE_SHHEALING
  mrb_define_method(mrb, cls_shape, "outerwire",  siren_heal_outerwire, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_method(mrb, cls_shape, "fix",        siren_heal_fix, MRB_ARGS_REQ(1));
#endif

  /* from BRepTools */
  mrb_define_method(mrb, cls_shape, "update!", siren_shape_update_bang, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "clean!",  siren_shape_clean_bang,  MRB_ARGS_NONE());

  /* frag accessors */
  mrb_define_method(mrb, cls_shape, "lock?",       siren_shape_is_lock,        MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "lock",        siren_shape_is_lock,        MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "lock=",       siren_shape_set_lock,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_shape, "modify?",     siren_shape_is_modify,      MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "modify",      siren_shape_is_modify,      MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "modify=",     siren_shape_set_modify,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_shape, "check?",      siren_shape_is_check,       MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "check",       siren_shape_is_check,       MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "check=",      siren_shape_set_check,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_shape, "orientable?", siren_shape_is_orientable,  MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "orientable",  siren_shape_is_orientable,  MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "orientable=", siren_shape_set_orientable, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_shape, "close?",      siren_shape_is_close,       MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "close",       siren_shape_is_close,       MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "close=",      siren_shape_set_close,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_shape, "infinite?",   siren_shape_is_infinite,    MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "infinite",    siren_shape_is_infinite,    MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "infinite=",   siren_shape_set_infinite,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls_shape, "convex?",     siren_shape_is_convex,      MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "convex",      siren_shape_is_convex,      MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "convex=",     siren_shape_set_convex,     MRB_ARGS_REQ(1));

  mrb_define_method(mrb, cls_shape, "next_trans",  siren_shape_next_trans,  MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_shape, "first_datum", siren_shape_first_datum,  MRB_ARGS_NONE());

  siren_vertex_install(mrb, mod_siren);
  siren_edge_install(mrb, mod_siren);
  siren_wire_install(mrb, mod_siren);
  siren_face_install(mrb, mod_siren);
  siren_shell_install(mrb, mod_siren);
  siren_solid_install(mrb, mod_siren);
#ifdef SIREN_ENABLE_CHUNK
  siren_chunk_install(mrb, mod_siren);
#endif
  siren_compound_install(mrb, mod_siren);

  return true;
}

mrb_value siren_shape_init(mrb_state* mrb, mrb_value self)
{
  mrb_raise(mrb, E_NOMETHOD_ERROR, "private method `new' called for Shape:Class");
  return mrb_nil_value();
}

void siren_shape_final(mrb_state* mrb, void* p)
{
  TopoDS_Shape* s = static_cast<TopoDS_Shape*>(p);
  s->Nullify();
  mrb_free(mrb, s);
}

mrb_value siren_shape_is_null(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  return shape->IsNull() ? mrb_true_value() : mrb_false_value();
}

mrb_value siren_shape_pos(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  gp_XYZ pos = shape->Location().Transformation().TranslationPart();
  return siren_pnt_to_ary(mrb, gp_Pnt(pos.X(), pos.Y(), pos.Z()));
}

mrb_value siren_shape_trans(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  TopLoc_Location loc = shape->Location();
  return siren_trans_new(mrb, loc.Transformation());
}

mrb_value siren_shape_next_trans(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  TopLoc_Location loc = shape->Location().NextLocation();
  return siren_trans_new(mrb, loc.Transformation());
}

mrb_value siren_shape_first_datum(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  TopLoc_Location loc = shape->Location();
  opencascade::handle<TopLoc_Datum3D> datum = loc.FirstDatum();
  gp_Trsf t = datum->Transformation();
  return siren_trans_new(mrb, t);
}

mrb_value siren_shape_set_trans(mrb_state* mrb, mrb_value self)
{
  mrb_value obj;
  int argc = mrb_get_args(mrb, "o", &obj);
  gp_Trsf* trans = siren_trans_get(mrb, obj);
  TopLoc_Location loc(*trans);
  siren_shape_get(mrb, self)->Location(loc);
  return self;
}

mrb_value siren_shape_bndbox(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  return siren_bndbox_new(mrb, *shape);
}

mrb_value siren_shape_translate_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value vec;
  int argc = mrb_get_args(mrb, "A", &vec);
  gp_Trsf trsf;
  trsf.SetTranslation(siren_ary_to_vec(mrb, vec));
  siren_shape_get(mrb, self)->Move(trsf);
  return self;
}

mrb_value siren_shape_rotate_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  mrb_float ang;
  int argc = mrb_get_args(mrb, "AAf", &op, &norm, &ang);
  gp_Trsf trsf;
  trsf.SetRotation(siren_ary_to_ax1(mrb, op, norm), ang);
  siren_shape_get(mrb, self)->Move(trsf);
  return self;
}

mrb_value siren_shape_scale_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op;
  mrb_float factor;
  int argc = mrb_get_args(mrb, "Af", &op, &factor);
  gp_Trsf trsf;
  trsf.SetScale(siren_ary_to_pnt(mrb, op), factor);
  siren_shape_get(mrb, self)->Move(trsf);
  return self;
}

mrb_value siren_shape_mirror_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  int argc = mrb_get_args(mrb, "AA", &op, &norm);
  gp_Trsf trsf;
  trsf.SetMirror(siren_ary_to_ax2(mrb, op, norm));
  siren_shape_get(mrb, self)->Move(trsf);
  return self;
}

mrb_value siren_shape_move_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value trans;
  int argc = mrb_get_args(mrb, "o", &trans);
  gp_Trsf* t = siren_trans_get(mrb, trans);
  siren_shape_get(mrb, self)->Move(*t);
  return self;
}

mrb_value siren_shape_translate(mrb_state* mrb, mrb_value self)
{
  mrb_value vec;
  int argc = mrb_get_args(mrb, "A", &vec);
  gp_Trsf trsf;
  trsf.SetTranslation(siren_ary_to_vec(mrb, vec));
  return siren_shape_new(mrb, siren_shape_get(mrb, self)->Moved(trsf));
}

mrb_value siren_shape_rotate(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  mrb_float ang;
  int argc = mrb_get_args(mrb, "AAf", &op, &norm, &ang);
  gp_Trsf trsf;
  trsf.SetRotation(siren_ary_to_ax1(mrb, op, norm), ang);
  return siren_shape_new(mrb, siren_shape_get(mrb, self)->Moved(trsf));
}

mrb_value siren_shape_scale(mrb_state* mrb, mrb_value self)
{
  mrb_value op;
  mrb_float factor;
  int argc = mrb_get_args(mrb, "Af", &op, &factor);
  gp_Trsf trsf;
  trsf.SetScale(siren_ary_to_pnt(mrb, op), factor);
  return siren_shape_new(mrb, siren_shape_get(mrb, self)->Moved(trsf));
}

mrb_value siren_shape_mirror(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  int argc = mrb_get_args(mrb, "AA", &op, &norm);
  gp_Trsf trsf;
  trsf.SetMirror(siren_ary_to_ax2(mrb, op, norm));
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
  mrb_value klass;
  mrb_value klassf;
  mrb_value block;
  int argc = mrb_get_args(mrb, "C|C&", &klass, &klassf, &block);

  mrb_value mtype;
  TopAbs_ShapeEnum type = TopAbs_COMPOUND;
  if (mrb_bool(mrb_funcall(mrb, klass, "==", 1, siren_compound_obj(mrb)))) {
    type = TopAbs_COMPOUND;
  }
  else if (mrb_bool(mrb_funcall(mrb, klass, "==", 1, siren_solid_obj(mrb)))) {
    type = TopAbs_SOLID;
  }
  else if (mrb_bool(mrb_funcall(mrb, klass, "==", 1, siren_shell_obj(mrb)))) {
    type = TopAbs_SHELL;
  }
  else if (mrb_bool(mrb_funcall(mrb, klass, "==", 1, siren_face_obj(mrb)))) {
    type = TopAbs_FACE;
  }
  else if (mrb_bool(mrb_funcall(mrb, klass, "==", 1, siren_wire_obj(mrb)))) {
    type = TopAbs_WIRE;
  }
  else if (mrb_bool(mrb_funcall(mrb, klass, "==", 1, siren_edge_obj(mrb)))) {
    type = TopAbs_EDGE;
  }
  else if (mrb_bool(mrb_funcall(mrb, klass, "==", 1, siren_vertex_obj(mrb)))) {
    type = TopAbs_VERTEX;
  }
  else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Type error.");
  }

  TopExp_Explorer ex;
  if (argc == 1) {
    ex.Init(*siren_shape_get(mrb, self), type);
  }
  else {
    mrb_value mfilter;
    TopAbs_ShapeEnum avoid = TopAbs_COMPOUND;
    if (mrb_bool(mrb_funcall(mrb, klassf, "==", 1, siren_compound_obj(mrb)))) {
      avoid = TopAbs_COMPOUND;
    }
    else if (mrb_bool(mrb_funcall(mrb, klassf, "==", 1, siren_solid_obj(mrb)))) {
      avoid = TopAbs_SOLID;
    }
    else if (mrb_bool(mrb_funcall(mrb, klassf, "==", 1, siren_shell_obj(mrb)))) {
      avoid = TopAbs_SHELL;
    }
    else if (mrb_bool(mrb_funcall(mrb, klassf, "==", 1, siren_face_obj(mrb)))) {
      avoid = TopAbs_FACE;
    }
    else if (mrb_bool(mrb_funcall(mrb, klassf, "==", 1, siren_wire_obj(mrb)))) {
      avoid = TopAbs_WIRE;
    }
    else if (mrb_bool(mrb_funcall(mrb, klassf, "==", 1, siren_edge_obj(mrb)))) {
      avoid = TopAbs_EDGE;
    }
    else if (mrb_bool(mrb_funcall(mrb, klassf, "==", 1, siren_vertex_obj(mrb)))) {
      avoid = TopAbs_VERTEX;
    }
    else {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "Type error.");
    }
    ex.Init(*siren_shape_get(mrb, self), type, avoid);
  }

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

mrb_value siren_shape_subshapes(mrb_state* mrb, mrb_value self)
{
  mrb_bool ori, loc;
  int argc = mrb_get_args(mrb, "|bb", &ori, &loc);
  if (argc == 0) {
    ori = TRUE;
    loc = TRUE;
  }
  if (argc == 1) {
    loc = TRUE;
  }
  mrb_value ar = mrb_ary_new(mrb);
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  if (!shape || shape->IsNull()) {
    return ar;
  }
  TopoDS_Iterator it(*shape, (Standard_Boolean)ori, (Standard_Boolean)loc);
  for (; it.More(); it.Next()) {
    mrb_int ai = mrb_gc_arena_save(mrb);
    mrb_ary_push(mrb, ar, siren_shape_new(mrb, it.Value()));
    mrb_gc_arena_restore(mrb, ai);
  }
  return ar;
}

mrb_value siren_shape_section(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);

  TopoDS_Shape* S1 = siren_shape_get(mrb, self);
  TopoDS_Shape* S2 = siren_shape_get(mrb, other);

  BRepAlgoAPI_Section api(*S1, *S2, Standard_False);
  // api.ComputePCurveOn1(Standard_True);
  api.Approximation(Standard_True);
  api.Build();

  if (!api.IsDone()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to intersection.");
  }

  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_shape_reverse(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  return siren_shape_new(mrb, shape->Reversed());
}

mrb_value siren_shape_reverse_bang(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  shape->Reverse();
  return mrb_nil_value();
}

mrb_value siren_shape_update_bang(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  BRepTools::Update(*shape);
  return self;
}

mrb_value siren_shape_clean_bang(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = siren_shape_get(mrb, self);
  // Removes all the triangulations of the faces of <shape>
  // and removes all polygons on triangulations of the edges.
  BRepTools::Clean(*shape);
  return self;
}

mrb_value siren_shape_is_lock(mrb_state* mrb, mrb_value self)
{
  return siren_shape_get(mrb, self)->Locked() == Standard_True ?
    mrb_true_value() : mrb_false_value();
}

mrb_value siren_shape_set_lock(mrb_state* mrb, mrb_value self)
{
  mrb_bool flag;
  int argc = mrb_get_args(mrb, "b", &flag);
  siren_shape_get(mrb, self)->Locked((Standard_Boolean)flag);
  return self;
}

mrb_value siren_shape_is_modify(mrb_state* mrb, mrb_value self)
{
  return siren_shape_get(mrb, self)->Modified() == Standard_True ?
    mrb_true_value() : mrb_false_value();
}

mrb_value siren_shape_set_modify(mrb_state* mrb, mrb_value self)
{
  mrb_bool flag;
  int argc = mrb_get_args(mrb, "b", &flag);
  siren_shape_get(mrb, self)->Modified((Standard_Boolean)flag);
  return self;
}

mrb_value siren_shape_is_check(mrb_state* mrb, mrb_value self)
{
  return siren_shape_get(mrb, self)->Checked() == Standard_True ?
    mrb_true_value() : mrb_false_value();
}

mrb_value siren_shape_set_check(mrb_state* mrb, mrb_value self)
{
  mrb_bool flag;
  int argc = mrb_get_args(mrb, "b", &flag);
  siren_shape_get(mrb, self)->Checked((Standard_Boolean)flag);
  return self;
}

mrb_value siren_shape_is_orientable(mrb_state* mrb, mrb_value self)
{
  return siren_shape_get(mrb, self)->Orientable() == Standard_True ?
    mrb_true_value() : mrb_false_value();
}

mrb_value siren_shape_set_orientable(mrb_state* mrb, mrb_value self)
{
  mrb_bool flag;
  int argc = mrb_get_args(mrb, "b", &flag);
  siren_shape_get(mrb, self)->Orientable((Standard_Boolean)flag);
  return self;
}

mrb_value siren_shape_is_close(mrb_state* mrb, mrb_value self)
{
  return siren_shape_get(mrb, self)->Closed() == Standard_True ?
    mrb_true_value() : mrb_false_value();
}

mrb_value siren_shape_set_close(mrb_state* mrb, mrb_value self)
{
  mrb_bool flag;
  int argc = mrb_get_args(mrb, "b", &flag);
  siren_shape_get(mrb, self)->Closed((Standard_Boolean)flag);
  return self;
}

mrb_value siren_shape_is_infinite(mrb_state* mrb, mrb_value self)
{
  return siren_shape_get(mrb, self)->Infinite() == Standard_True ?
    mrb_true_value() : mrb_false_value();
}

mrb_value siren_shape_set_infinite(mrb_state* mrb, mrb_value self)
{
  mrb_bool flag;
  int argc = mrb_get_args(mrb, "b", &flag);
  siren_shape_get(mrb, self)->Infinite((Standard_Boolean)flag);
  return self;
}

mrb_value siren_shape_is_convex(mrb_state* mrb, mrb_value self)
{
  return siren_shape_get(mrb, self)->Convex() == Standard_True ?
    mrb_true_value() : mrb_false_value();
}

mrb_value siren_shape_set_convex(mrb_state* mrb, mrb_value self)
{
  mrb_bool flag;
  int argc = mrb_get_args(mrb, "b", &flag);
  siren_shape_get(mrb, self)->Convex((Standard_Boolean)flag);
  return self;
}

