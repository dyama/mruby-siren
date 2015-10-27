#include "trans.h"

gp_Trsf* siren_trans_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<gp_Trsf*>(mrb_get_datatype(mrb, obj, &siren_trans_type));
}

/*
#include <TopLoc_Datum3D.hxx>
mrb_value siren_trans_test(mrb_state* mrb, mrb_value self)
{
  gp_Trsf t1; t1.SetTranslation(gp_Vec(1.0, 0.0, 0.0));
  gp_Trsf t2; t2.SetTranslation(gp_Vec(10.0, 0.0, 0.0));
  gp_Trsf t3; t3.SetTranslation(gp_Vec(2.0, 0.0, 0.0));
  gp_Trsf t4; t4.SetTranslation(gp_Vec(3.0, 0.0, 0.0));

  Handle(TopLoc_Datum3D) R1 = new TopLoc_Datum3D(t1);
  Handle(TopLoc_Datum3D) R2 = new TopLoc_Datum3D(t2);
  Handle(TopLoc_Datum3D) R3 = new TopLoc_Datum3D(t3);
  Handle(TopLoc_Datum3D) R4 = new TopLoc_Datum3D(t4);

  TopLoc_Location L1(R1);
  TopLoc_Location L2(R2);
  TopLoc_Location L3(R3);
  TopLoc_Location L4(R4);

  TopoDS_Shape S1 = BRepBuilderAPI_MakeVertex(gp_Pnt(0.0, 0.0, 0.0));
  // TopoDS_Shape S2 = BRepBuilderAPI_MakeVertex(gp_Pnt(0.0, 0.0, 0.0));

  S1.Move(L1);
  S1.Move(L2);
  S1.Move(L3);

  //S2.Move(L1);
  //S2.Move(L2);
  //S2.Move(L4);

  TopLoc_Location loc1 = S1.Location();
  TopLoc_Location loc2 = loc1.NextLocation();
  TopLoc_Location loc3 = loc2.NextLocation();
  gp_Trsf T1 = loc1.Transformation(); // 
  gp_Trsf T2 = loc2.Transformation(); // 
  gp_Trsf T3 = loc3.Transformation();

  gp_Trsf T11 = loc1.FirstDatum()->Transformation();
  gp_Trsf T12 = loc2.FirstDatum()->Transformation();
  gp_Trsf T13 = loc3.FirstDatum()->Transformation();

  // TopLoc_Location loc21 = S2.Location();
  // TopLoc_Location loc22 = loc21.NextLocation();
  // TopLoc_Location loc23 = loc22.NextLocation();
  // gp_Trsf T21 = loc21.Transformation();
  // gp_Trsf T22 = loc22.Transformation();
  // gp_Trsf T23 = loc23.Transformation();

  mrb_value res = mrb_ary_new(mrb);
  //mrb_ary_push(mrb, res, siren_trans_new(mrb, T1));
  //mrb_ary_push(mrb, res, siren_trans_new(mrb, T2));
  //mrb_ary_push(mrb, res, siren_trans_new(mrb, T3));
  mrb_ary_push(mrb, res, siren_trans_new(mrb, T11));
  mrb_ary_push(mrb, res, siren_trans_new(mrb, T12));
  mrb_ary_push(mrb, res, siren_trans_new(mrb, T13));

  return res;
}
*/

mrb_value siren_trans_new(mrb_state* mrb, const gp_Trsf& src)
{
  mrb_value res;
  res = mrb_instance_alloc(mrb, mrb_obj_value(mrb_class_get(mrb, "Trans")));
  void* p = mrb_malloc(mrb, sizeof(gp_Trsf));
  gp_Trsf* trans = new(p) gp_Trsf();
  *trans = src;
  DATA_PTR(res) = trans;
  DATA_TYPE(res) = &siren_trans_type;
  return res;
}

bool siren_trans_install(mrb_state* mrb, struct RClass* rclass)
{
  rclass = mrb_define_class(mrb, "Trans", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_method(mrb, rclass, "initialize"     , siren_trans_init               , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "inspect"        , siren_trans_to_s               , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_s"           , siren_trans_to_s               , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_a"           , siren_trans_to_a               , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "to_ary"         , siren_trans_to_a               , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "multiply"       , siren_trans_multiply           , MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "multiply!"      , siren_trans_multiply_bang      , MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "scalef"         , siren_trans_scalef             , MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "mirror!"        , siren_trans_mirror_bang        , MRB_ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "rotation!"      , siren_trans_rotation_bang      , MRB_ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "scale!"         , siren_trans_scale_bang         , MRB_ARGS_REQ(2));
  mrb_define_method(mrb, rclass, "scalef!"        , siren_trans_scalef_bang        , MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "transfomation1!", siren_trans_transfomation1_bang, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "transfomation2!", siren_trans_transfomation2_bang, MRB_ARGS_REQ(6));
  mrb_define_method(mrb, rclass, "translation!"   , siren_trans_translation_bang   , MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "move_point"     , siren_trans_move_point         , MRB_ARGS_REQ(1));

  // mrb_define_method(mrb, rclass, "test"     , siren_trans_test         , MRB_ARGS_NONE());
  // mrb_define_method(mrb, rclass, "matrix",        , siren_trans_translation_bang   , MRB_ARGS_REQ(1));
  return true;
}

mrb_value siren_trans_init(mrb_state* mrb, mrb_value self)
{
  void* p = mrb_malloc(mrb, sizeof(gp_Trsf));
  gp_Trsf* trans = new(p) gp_Trsf();
  DATA_PTR(self) = trans;
  DATA_TYPE(self) = &siren_trans_type;
  return self;
}

void siren_trans_final(mrb_state* mrb, void* p)
{
  gp_Trsf* t = static_cast<gp_Trsf*>(p);
  mrb_free(mrb, t);
}

mrb_value siren_trans_to_s(mrb_state* mrb, mrb_value self)
{
  char str[256];
  Standard_Real a11 = siren_trans_get(mrb, self)->Value(1, 1);
  Standard_Real a12 = siren_trans_get(mrb, self)->Value(1, 2);
  Standard_Real a13 = siren_trans_get(mrb, self)->Value(1, 3);
  Standard_Real a14 = siren_trans_get(mrb, self)->Value(1, 4);
  Standard_Real a21 = siren_trans_get(mrb, self)->Value(2, 1);
  Standard_Real a22 = siren_trans_get(mrb, self)->Value(2, 2);
  Standard_Real a23 = siren_trans_get(mrb, self)->Value(2, 3);
  Standard_Real a24 = siren_trans_get(mrb, self)->Value(2, 4);
  Standard_Real a31 = siren_trans_get(mrb, self)->Value(3, 1);
  Standard_Real a32 = siren_trans_get(mrb, self)->Value(3, 2);
  Standard_Real a33 = siren_trans_get(mrb, self)->Value(3, 3);
  Standard_Real a34 = siren_trans_get(mrb, self)->Value(3, 4);
  snprintf(str, sizeof(str),
      "#<Trans:0x%x\n"
      "    X = %.6f, %.6f, %.6f\n"
      "    Y = %.6f, %.6f, %.6f\n"
      "    Z = %.6f, %.6f, %.6f\n"
      "    T = %.6f, %.6f, %.6f>",
      (int)mrb_cptr(self),
      a11, a21, a31,
      a12, a22, a32,
      a13, a23, a33,
      a14, a24, a34
      );
  return mrb_str_new_cstr(mrb, str);
}

mrb_value siren_trans_to_a(mrb_state* mrb, mrb_value self)
{
  mrb_value result[4];
  for (int row = 1; row <= 4; row++) {
    result[row - 1] = mrb_ary_new(mrb);
    for (int col = 1; col <= 3; col++) {
      mrb_ary_push(mrb, result[row - 1], 
          mrb_float_value(mrb, siren_trans_get(mrb, self)->Value(row, col)));
    }
  }
  return mrb_ary_new_from_values(mrb, 4, result);
}

mrb_value siren_trans_translation_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value v;
  int argc = mrb_get_args(mrb, "A", &v);
  gp_Vec vec = siren_ary_to_vec(mrb, v); 
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetTranslation(vec);
  return mrb_nil_value();
}

mrb_value siren_trans_rotation_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  mrb_float angle;
  int argc = mrb_get_args(mrb, "AAf", &op, &norm, &angle);
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetRotation(siren_ary_to_ax1(mrb, op, norm), angle);
  return mrb_nil_value();
}

mrb_value siren_trans_scale_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op;
  mrb_float factor;
  int argc = mrb_get_args(mrb, "Af", &op, &factor);
  gp_Trsf* trans  = siren_trans_get(mrb, self);
  trans->SetScale(siren_ary_to_pnt(mrb, op), factor);
  return mrb_nil_value();
}

mrb_value siren_trans_scalef(mrb_state* mrb, mrb_value self)
{
  gp_Trsf* trans  = siren_trans_get(mrb, self);
  Standard_Real f = trans->ScaleFactor();
  return mrb_float_value(mrb, f);
}

mrb_value siren_trans_scalef_bang(mrb_state* mrb, mrb_value self)
{
  mrb_float f;
  int argc = mrb_get_args(mrb, "f", &f);
  gp_Trsf* trans  = siren_trans_get(mrb, self);
  trans->SetScaleFactor(f);
  return mrb_nil_value();
}

mrb_value siren_trans_mirror_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op, norm;
  int argc = mrb_get_args(mrb, "AA", &op, &norm);
  gp_Trsf* trans    = siren_trans_get(mrb, self);
  trans->SetMirror(siren_ary_to_ax2(mrb, op, norm));
  return mrb_nil_value();
}

mrb_value siren_trans_multiply_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  gp_Trsf* trans_me = siren_trans_get(mrb, self);
  gp_Trsf* trans_other = siren_trans_get(mrb, other);
  trans_me->Multiply(*trans_other);
  return mrb_nil_value();
}

mrb_value siren_trans_multiply(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  int argc = mrb_get_args(mrb, "o", &other);
  gp_Trsf* trans_me = siren_trans_get(mrb, self);
  gp_Trsf* trans_other = siren_trans_get(mrb, other);
  mrb_value res = mrb_class_new_instance(mrb, 0, NULL, mrb_class_get(mrb, "Trans"));
  gp_Trsf* t = siren_trans_get(mrb, res);
  *t = trans_me->Multiplied(*trans_other);
  return res;
}

mrb_value siren_trans_transfomation1_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op, zv, xv;
  int argc = mrb_get_args(mrb, "AAA", &op, &zv, &xv);
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetTransformation(siren_ary_to_ax3(mrb, op, zv, xv));
  return mrb_nil_value();
}

mrb_value siren_trans_transfomation2_bang(mrb_state* mrb, mrb_value self)
{
  mrb_value op1, zv1, xv1;
  mrb_value op2, zv2, xv2;
  int argc = mrb_get_args(mrb, "AAAAAA", &op1, &zv1, &xv1, &op2, &zv2, &xv2);
  gp_Trsf* trans = siren_trans_get(mrb, self);
  trans->SetTransformation(siren_ary_to_ax3(mrb, op1, zv1, xv1), siren_ary_to_ax3(mrb, op2, zv2, xv2));
  return mrb_nil_value();
}

mrb_value siren_trans_value(mrb_state* mrb, mrb_value self)
{
  return mrb_nil_value();
}

mrb_value siren_trans_set_value(mrb_state* mrb, mrb_value self)
{
  return mrb_nil_value();
}

mrb_value siren_trans_move_point(mrb_state* mrb, mrb_value self)
{
  mrb_value ary;
  int argc = mrb_get_args(mrb, "A", &ary);
  gp_Pnt point = siren_ary_to_pnt(mrb, ary);
  gp_Trsf* trans = siren_trans_get(mrb, self);
  point.Transform(*trans);
  return siren_pnt_to_ary(mrb, point);
}

