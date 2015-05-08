#ifndef _COMMON_H_
#define _COMMON_H_

#include "mruby.h"
#include "shape.h"

#include <gp_Vec.hxx>
#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax3.hxx>

void siren_ary_to_xyz(mrb_state* mrb, mrb_value ary, Standard_Real& x, Standard_Real& y, Standard_Real& z);

inline gp_Pnt siren_ary_to_pnt(mrb_state* mrb, mrb_value val)
{
  Standard_Real x, y, z;
  siren_ary_to_xyz(mrb, val, x, y, z);
  return gp_Pnt(x, y, z);
}

inline gp_Vec siren_ary_to_vec(mrb_state* mrb, mrb_value val)
{
  Standard_Real x, y, z;
  siren_ary_to_xyz(mrb, val, x, y, z);
  return gp_Vec(x, y, z);
}

inline gp_Dir siren_ary_to_dir(mrb_state* mrb, mrb_value val)
{
  Standard_Real x, y, z;
  siren_ary_to_xyz(mrb, val, x, y, z);
  return gp_Dir(x, y, z);
}

inline gp_Ax1 siren_ary_to_ax1(mrb_state* mrb, mrb_value pos, mrb_value norm)
{
  return gp_Ax1(siren_ary_to_pnt(mrb, pos), siren_ary_to_dir(mrb, norm));
}

inline gp_Ax2 siren_ary_to_ax2(mrb_state* mrb, mrb_value pos, mrb_value norm, mrb_value vdir)
{
  return gp_Ax2(siren_ary_to_pnt(mrb, pos), siren_ary_to_dir(mrb, norm), siren_ary_to_dir(mrb, vdir));
}

inline gp_Ax2 siren_ary_to_ax2(mrb_state* mrb, mrb_value pos, mrb_value norm)
{
  return gp_Ax2(siren_ary_to_pnt(mrb, pos), siren_ary_to_dir(mrb, norm));
}

inline gp_Ax3 siren_ary_to_ax3(mrb_state* mrb, mrb_value pos, mrb_value norm, mrb_value vdir)
{
  return gp_Ax3(siren_ary_to_pnt(mrb, pos), siren_ary_to_dir(mrb, norm), siren_ary_to_dir(mrb, vdir));
}

inline gp_Ax3 siren_ary_to_ax3(mrb_state* mrb, mrb_value pos, mrb_value norm)
{
  return gp_Ax3(siren_ary_to_pnt(mrb, pos), siren_ary_to_dir(mrb, norm));
}

mrb_value mrb_instance_alloc(mrb_state *mrb, mrb_value cv);

#endif
