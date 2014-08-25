#ifndef _COMMON_H_
#define _COMMON_H_

#include "shape.h"

inline double to_double(const mrb_value& value)
{
  double res = 0.0;
  if (mrb_nil_p(value))
    res = 0.0;
  else if (mrb_float_p(value))
    res = value.value.f;
  else if (mrb_fixnum_p(value))
    res = mrb_fixnum(value);
  else
    throw "value is not numric value.";
  return res;
}

// inline gp_Pnt ar2pnt(mrb_state* mrb, mrb_value ary)
// {
//   double x = to_double(mrb_ary_ref(mrb, ary, 0));
//   double y = to_double(mrb_ary_ref(mrb, ary, 1));
//   double z = to_double(mrb_ary_ref(mrb, ary, 2));
//   return gp_Pnt(x, y, z);
// }
// 
// inline gp_Vec ar2vec(mrb_state* mrb, mrb_value ary)
// {
//   double x = to_double(mrb_ary_ref(mrb, ary, 0));
//   double y = to_double(mrb_ary_ref(mrb, ary, 1));
//   double z = to_double(mrb_ary_ref(mrb, ary, 2));
//   return gp_Vec(x, y, z);
// }
// 
// inline gp_Dir ar2dir(mrb_state* mrb, mrb_value ary)
// {
//   double x = to_double(mrb_ary_ref(mrb, ary, 0));
//   double y = to_double(mrb_ary_ref(mrb, ary, 1));
//   double z = to_double(mrb_ary_ref(mrb, ary, 2));
//   return gp_Dir(x, y, z);
// }
// 
// inline mrb_value pnt2ar(mrb_state* mrb, const gp_Pnt& pnt)
// {
//   // http://wasabiz.hatenablog.com/entry/2013/08/07/144145
//   gp_Pnt p = gp_Pnt((float)pnt.X(), (float)pnt.Y(), (float)pnt.Z());
// 
//   mrb_value res[3];
//   res[0] = mrb_float_value(mrb, p.X());
//   res[1] = mrb_float_value(mrb, p.Y());
//   res[2] = mrb_float_value(mrb, p.Z());
//   return mrb_ary_new_from_values(mrb, 3, res);
// }
// 
// inline mrb_value vec2ar(mrb_state* mrb, const gp_Vec& vec)
// {
//   // http://wasabiz.hatenablog.com/entry/2013/08/07/144145
//   gp_Vec v = gp_Vec((float)vec.X(), (float)vec.Y(), (float)vec.Z());
// 
//   mrb_value res[3];
//   res[0] = mrb_float_value(mrb, v.X());
//   res[1] = mrb_float_value(mrb, v.Y());
//   res[2] = mrb_float_value(mrb, v.Z());
//   return mrb_ary_new_from_values(mrb, 3, res);
// }

inline mrb_value mrb_siren_shape_new(mrb_state* mrb, const TopoDS_Shape* shape)
{
  mrb_value res = mrb_class_new_instance(mrb, 0, NULL, mrb_class_get(mrb, "Shape"));
  DATA_PTR(res) = static_cast<void*>(const_cast<TopoDS_Shape*>(shape));
  return res;
}

#endif
