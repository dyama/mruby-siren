#include "shape/solid.h"

mrb_value siren_solid_new(mrb_state* mrb, const TopoDS_Shape* src)
{
  mrb_value obj;
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  obj = mrb_instance_alloc(mrb, mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Solid")));
  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = *src; // Copy to inner native member
  DATA_PTR(obj)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(obj) = &siren_solid_type;
  return obj;
}

TopoDS_Solid siren_solid_get(mrb_state* mrb, mrb_value self)
{
  TopoDS_Shape* shape = static_cast<TopoDS_Shape*>(mrb_get_datatype(mrb, self, &siren_solid_type));
  TopoDS_Solid solid = TopoDS::Solid(*shape);
  if (solid.IsNull()) { mrb_raise(mrb, E_RUNTIME_ERROR, "The geometry type is not Solid."); }
  return solid;
}

bool siren_solid_install(mrb_state* mrb, struct RClass* mod_siren)
{
  struct RClass* cls_shape = siren_shape_rclass(mrb);
  struct RClass* cls_solid = mrb_define_class_under(mrb, mod_siren, "Solid", cls_shape);
  MRB_SET_INSTANCE_TT(cls_solid, MRB_TT_DATA);
  mrb_define_method(mrb, cls_solid, "initialize", siren_solid_init, MRB_ARGS_NONE());

  auto obj_solid = mrb_obj_ptr(siren_solid_obj(mrb));
  mrb_define_singleton_method(mrb, obj_solid, "box",        siren_solid_box,        MRB_ARGS_OPT(2));
  mrb_define_singleton_method(mrb, obj_solid, "box2p",      siren_solid_box2p,      MRB_ARGS_OPT(2));
  mrb_define_singleton_method(mrb, obj_solid, "boxax",      siren_solid_boxax,      MRB_ARGS_REQ(3));
  mrb_define_singleton_method(mrb, obj_solid, "sphere",     siren_solid_sphere,     MRB_ARGS_OPT(2));
  mrb_define_singleton_method(mrb, obj_solid, "cylinder",   siren_solid_cylinder,   MRB_ARGS_REQ(5));
  mrb_define_singleton_method(mrb, obj_solid, "cone",       siren_solid_cone,       MRB_ARGS_REQ(6));
  mrb_define_singleton_method(mrb, obj_solid, "torus",      siren_solid_torus,      MRB_ARGS_REQ(5));
  mrb_define_singleton_method(mrb, obj_solid, "halfspace",  siren_solid_halfspace,  MRB_ARGS_REQ(2));
  mrb_define_singleton_method(mrb, obj_solid, "prism",      siren_solid_prism,      MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, obj_solid, "revol",      siren_solid_revol,      MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, obj_solid, "revolution", siren_solid_revolution, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, obj_solid, "wedge",      siren_solid_wedge,      MRB_ARGS_OPT(7));
  return true;
}

struct RClass* siren_solid_rclass(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Solid")));
}

mrb_value siren_solid_obj(mrb_state* mrb)
{
  struct RClass* mod_siren = mrb_module_get(mrb, "Siren");
  return mrb_const_get(mrb, mrb_obj_value(mod_siren), mrb_intern_lit(mrb, "Solid"));
}

mrb_value siren_solid_init(mrb_state* mrb, mrb_value self)
{
  mrb_value* a;
  mrb_int len;
  int argc = mrb_get_args(mrb, "*", &a, &len);
  if (len == 0) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "No shapes specified.");
  }
  BRepBuilderAPI_MakeSolid solid_maker;
  for (int i = 0; i < len; i++) {
    TopoDS_Shell shell = siren_shell_get(mrb, a[i]);
    solid_maker.Add(shell);
  }
  if (!solid_maker.IsDone()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Failed to make a Solid.");
  }
  TopoDS_Shape shape = solid_maker.Shape();
  if (shape.IsNull()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Failed to make a Solid.");
  }
  void* p = mrb_malloc(mrb, sizeof(TopoDS_Shape));
  TopoDS_Shape* inner = new(p) TopoDS_Shape();
  *inner = shape; // Copy to inner native member
  DATA_PTR(self)  = const_cast<TopoDS_Shape*>(inner);
  DATA_TYPE(self) = &siren_solid_type;
  return self;
}

mrb_value siren_solid_box(mrb_state* mrb, mrb_value self)
{
  mrb_value size, pos;
  int argc = mrb_get_args(mrb, "|AA", &size, &pos);

  Standard_Real sx, sy, sz;
  if (argc >= 1) {
    siren_ary_to_xyz(mrb, size, sx, sy, sz);
  }
  else {
    sx = 1.0; sy = 1.0; sz = 1.0;
  }

  gp_Pnt op;
  if (argc >= 2) {
    Standard_Real px, py, pz;
    siren_ary_to_xyz(mrb, pos, px, py, pz);
    op = gp_Pnt(px, py, pz);
  }
  else {
    op = gp_Pnt(0., 0., 0.);
  }
  if (std::fabs(sx * sy * sz) == 0.0) {
    mrb_raise(mrb, E_ARGUMENT_ERROR,
      "Failed to make solid. Incorrect size specified.");
  }
  BRepPrimAPI_MakeBox api(op, sx, sy, sz);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_solid_box2p(mrb_state* mrb, mrb_value self)
{
  mrb_value p1, p2;
  int argc = mrb_get_args(mrb, "|AA", &p1, &p2);

  Standard_Real x1 = 0.0, y1 = 0.0, z1 = 0.0;
  Standard_Real x2 = 1.0, y2 = 1.0, z2 = 1.0;

  if (argc >= 1) {
    siren_ary_to_xyz(mrb, p1, x1, y1, z1);
  }
  if (argc >= 2) {
    siren_ary_to_xyz(mrb, p2, x2, y2, z2);
  }

  gp_Pnt point1(x1, x1, x1);
  gp_Pnt point2(x2, x2, x2);

  BRepPrimAPI_MakeBox api(point1, point2);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_solid_boxax(mrb_state* mrb, mrb_value self)
{
  mrb_value size, pos, dir;
  int argc = mrb_get_args(mrb, "AAA", &size, &pos, &dir);

  Standard_Real sx, sy, sz;
  siren_ary_to_xyz(mrb, size, sx, sy, sz);

  Standard_Real px, py, pz;
  siren_ary_to_xyz(mrb, pos, px, py, pz);

  Standard_Real dx, dy, dz;
  siren_ary_to_xyz(mrb, dir, dx, dy, dz);

  gp_Ax2 ax(gp_Pnt(px, py, pz), gp_Dir(dx, dy, dz));

  BRepPrimAPI_MakeBox api(ax, sx, sy, sz);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_solid_sphere(mrb_state* mrb, mrb_value self)
{
  mrb_float r = 1.0;
  mrb_value pos;
  int argc = mrb_get_args(mrb, "|fA", &r, &pos);

  gp_Pnt op;
  if (argc == 2) {
    Standard_Real px, py, pz;
    siren_ary_to_xyz(mrb, pos, px, py, pz);
    op = gp_Pnt(px, py, pz);
  }
  else {
    op = gp_Pnt(0., 0., 0.);
  }

  if (r < 0) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make solid."
      " Specified radius value below 0.");
  }

  BRepPrimAPI_MakeSphere api(op, r);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_solid_cylinder(mrb_state* mrb, mrb_value self)
{
  mrb_value pos, norm;
  mrb_float r, h, a;
  int argc = mrb_get_args(mrb, "AAfff", &pos, &norm, &r, &h, &a);

  gp_Ax2 ax = siren_ary_to_ax2(mrb, pos, norm);

  BRepPrimAPI_MakeCylinder api(ax, r, h, a);

  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_solid_cone(mrb_state* mrb, mrb_value self)
{
  mrb_value pos, norm;
  mrb_float r1, r2, h, ang;
  int argc = mrb_get_args(mrb, "AAffff", &pos, &norm, &r1, &r2, &h, &ang);

  gp_Ax2 ax = siren_ary_to_ax2(mrb, pos, norm);

  BRepPrimAPI_MakeCone api(ax, r1, r2, h, ang);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_solid_torus(mrb_state* mrb, mrb_value self)
{
  mrb_float r1, r2, ang;
  mrb_value pos, norm;
  int argc = mrb_get_args(mrb, "AAfff", &pos, &norm, &r1, &r2, &ang);

  gp_Ax2 ax = siren_ary_to_ax2(mrb, pos, norm);

  BRepPrimAPI_MakeTorus api(ax, r1, r2, ang);
  return siren_shape_new(mrb, api.Shape());
}

mrb_value siren_solid_halfspace(mrb_state* mrb, mrb_value self)
{
  mrb_value surf, refpnt;
  int argc = mrb_get_args(mrb, "oA", &surf, &refpnt);
  TopoDS_Shape* shape = siren_shape_get(mrb, surf);
  if (shape == nullptr || shape->IsNull()) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Specified shape is incorrect.");
  }
  TopoDS_Solid solid;
  gp_Pnt pnt = siren_ary_to_pnt(mrb, refpnt);
  if (shape->ShapeType() == TopAbs_FACE) {
    solid = BRepPrimAPI_MakeHalfSpace(TopoDS::Face(*shape), pnt);
  }
  else if (shape->ShapeType() == TopAbs_SHELL) {
    solid = BRepPrimAPI_MakeHalfSpace(TopoDS::Shell(*shape), pnt);
  }
  else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Specified shape type is not FACE or SHELL.");
  }
  return siren_shape_new(mrb, solid);
}

mrb_value siren_solid_prism(mrb_state* mrb, mrb_value self)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented.");
  return mrb_nil_value();
}

mrb_value siren_solid_revol(mrb_state* mrb, mrb_value self)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented.");
  return mrb_nil_value();
}

mrb_value siren_solid_revolution(mrb_state* mrb, mrb_value self)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented.");
  return mrb_nil_value();
}

mrb_value siren_solid_wedge(mrb_state* mrb, mrb_value self)
{
  mrb_float dx = 1.0, dy = 1.0, dz = 1.0, x = 0.5, z = 0.5, X = 0.5, Z = 0.5;
  int argc = mrb_get_args(mrb, "|fffffff", &dx, &dy, &dz, &x, &z, &X, &Z);
  try {
    BRepPrimAPI_MakeWedge api(dx, dy, dz, x, z, X, Z);
    TopoDS_Shape s = api.Shape();
    return siren_shape_new(mrb, s);
  }
  catch (...) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Failed to make a wedge.");
  }
  return mrb_nil_value();
}

