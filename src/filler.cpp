#include "filler.h"

BRepFill_Filling* siren_filler_get(mrb_state* mrb, mrb_value obj)
{
  return static_cast<BRepFill_Filling*>(mrb_get_datatype(mrb, obj, &siren_filler_type));
}

bool siren_filler_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_filler = mrb_define_class_under(mrb, mod_siren, "Filler", mrb->object_class);
  MRB_SET_INSTANCE_TT(cls_filler, MRB_TT_DATA);
  mrb_define_method(mrb, cls_filler, "initialize", siren_filler_init,      MRB_ARGS_OPT(10));
  mrb_define_method(mrb, cls_filler, "add_bound",  siren_filler_add_bound, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, cls_filler, "add",        siren_filler_add,       MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_method(mrb, cls_filler, "build",      siren_filler_build,     MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_filler, "done?",      siren_filler_is_done,   MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_filler, "face",       siren_filler_face,      MRB_ARGS_NONE());
  mrb_define_method(mrb, cls_filler, "g0error",    siren_filler_g0error,   MRB_ARGS_OPT(1));
  mrb_define_method(mrb, cls_filler, "g1error",    siren_filler_g1error,   MRB_ARGS_OPT(1));
  mrb_define_method(mrb, cls_filler, "g2error",    siren_filler_g2error,   MRB_ARGS_OPT(1));
  return true;
}

mrb_value siren_filler_init(mrb_state* mrb, mrb_value self)
{
  mrb_int degree, nbptsoncur, nbiter;
  mrb_bool anisotropie;
  mrb_float tol2d, tol3d, tolang, tolcurv;
  mrb_int maxdeg, maxsegs;
  int argc = mrb_get_args(mrb, "|iiibffffii",
      &degree, &nbptsoncur, &nbiter, &anisotropie,
      &tol2d, &tol3d, &tolang, &tolcurv, &maxdeg, &maxsegs);

  void* p = mrb_malloc(mrb, sizeof(BRepFill_Filling));
  BRepFill_Filling* inner = NULL;

  switch (argc) {
    case 1:
      inner = new(p) BRepFill_Filling(degree);
      break;
    case 2:
      inner = new(p) BRepFill_Filling(degree, nbptsoncur);
      break;
    case 3:
      inner = new(p) BRepFill_Filling(degree, nbptsoncur, nbiter);
      break;
    case 4:
      inner = new(p) BRepFill_Filling(degree, nbptsoncur, nbiter, anisotropie);
      break;
    case 5:
      inner = new(p) BRepFill_Filling(degree, nbptsoncur, nbiter, anisotropie,
          tol2d);
      break;
    case 6:
      inner = new(p) BRepFill_Filling(degree, nbptsoncur, nbiter, anisotropie,
          tol2d, tol3d);
      break;
    case 7:
      inner = new(p) BRepFill_Filling(degree, nbptsoncur, nbiter, anisotropie,
          tol2d, tol3d, tolang);
      break;
    case 8:
      inner = new(p) BRepFill_Filling(degree, nbptsoncur, nbiter, anisotropie,
          tol2d, tol3d, tolang, tolcurv);
      break;
    case 9:
      inner = new(p) BRepFill_Filling(degree, nbptsoncur, nbiter, anisotropie,
          tol2d, tol3d, tolang, tolcurv, maxdeg);
      break;
    case 10:
      inner = new(p) BRepFill_Filling(degree, nbptsoncur, nbiter, anisotropie,
          tol2d, tol3d, tolang, tolcurv, maxdeg, maxsegs);
      break;
    default:
      inner = new(p) BRepFill_Filling();
      break;
  }

  DATA_PTR(self)  = inner;
  DATA_TYPE(self) = &siren_filler_type;
  return self;
}

void siren_filler_final(mrb_state* mrb, void* p)
{
  BRepFill_Filling* pp = static_cast<BRepFill_Filling*>(p);
  mrb_free(mrb, pp);
}

mrb_value siren_filler_add_bound(mrb_state* mrb, mrb_value self)
{
  mrb_value edge;
  mrb_int order;
  int argc = mrb_get_args(mrb, "oi", &edge, &order);
  TopoDS_Shape* s = siren_shape_get(mrb, edge);
  TopoDS_Edge e = TopoDS::Edge(*s);
  siren_filler_get(mrb, self)->Add(e, (GeomAbs_Shape)order,
      /* IsBound= */ Standard_True);
  return mrb_nil_value();
}

mrb_value siren_filler_add(mrb_state* mrb, mrb_value self)
{
  mrb_value obj;
  mrb_int order;
  int argc = mrb_get_args(mrb, "o|i", &obj, &order);
  if (argc == 2) {
    TopoDS_Shape* s = siren_shape_get(mrb, obj);
    TopoDS_Edge e = TopoDS::Edge(*s);
    siren_filler_get(mrb, self)->Add(e, (GeomAbs_Shape)order,
        /* IsBound= */ Standard_False);
  }
  else {
    gp_Pnt pnt = siren_ary_to_pnt(mrb, obj);
    siren_filler_get(mrb, self)->Add(pnt);
  }
  return mrb_nil_value();
}

mrb_value siren_filler_build(mrb_state* mrb, mrb_value self)
{
  siren_filler_get(mrb, self)->Build();
  return mrb_nil_value();
}

mrb_value siren_filler_is_done(mrb_state* mrb, mrb_value self)
{
  return siren_filler_get(mrb, self)->IsDone() == Standard_True ?
    mrb_true_value() : mrb_false_value();
}

mrb_value siren_filler_face(mrb_state* mrb, mrb_value self)
{
  TopoDS_Face f = siren_filler_get(mrb, self)->Face();
  return siren_shape_new(mrb, f);
}

mrb_value siren_filler_g0error(mrb_state* mrb, mrb_value self)
{
  mrb_int index;
  int argc = mrb_get_args(mrb, "|i", &index);
  Standard_Real value;
  if (argc) {
    value = siren_filler_get(mrb, self)->G0Error(index);
  }
  else {
    value = siren_filler_get(mrb, self)->G0Error();
  }
  return mrb_float_value(mrb, value);
}

mrb_value siren_filler_g1error(mrb_state* mrb, mrb_value self)
{
  mrb_int index;
  int argc = mrb_get_args(mrb, "|i", &index);
  Standard_Real value;
  if (argc) {
    value = siren_filler_get(mrb, self)->G1Error(index);
  }
  else {
    value = siren_filler_get(mrb, self)->G1Error();
  }
  return mrb_float_value(mrb, value);
}

mrb_value siren_filler_g2error(mrb_state* mrb, mrb_value self)
{
  mrb_int index;
  int argc = mrb_get_args(mrb, "|i", &index);
  Standard_Real value;
  if (argc) {
    value = siren_filler_get(mrb, self)->G2Error(index);
  }
  else {
    value = siren_filler_get(mrb, self)->G2Error();
  }
  return mrb_float_value(mrb, value);
}

