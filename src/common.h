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

inline gp_Pnt vec2pnt(const gp_Vec* vec)
{
  return gp_Pnt(vec->X(), vec->Y(), vec->Z());
}

inline gp_Dir vec2dir(const gp_Vec* vec)
{
  return gp_Dir(vec->X(), vec->Y(), vec->Z());
}

inline gp_Ax1 vec2ax1(const gp_Vec* p, const gp_Vec* v)
{
  return gp_Ax1(vec2pnt(p), vec2dir(v));
}

inline gp_Ax2 vec2ax2(const gp_Vec* p, const gp_Vec* n, const gp_Vec* vx)
{
  return gp_Ax2(vec2pnt(p), vec2dir(n), vec2dir(vx));
}

inline gp_Ax2 vec2ax2(const gp_Vec* p, const gp_Vec* v)
{
  return gp_Ax2(vec2pnt(p), vec2dir(v));
}

inline gp_Ax3 vec2ax3(const gp_Vec* p, const gp_Vec* n, const gp_Vec* vx)
{
  return gp_Ax3(vec2pnt(p), vec2dir(n), vec2dir(vx));
}

inline gp_Ax3 vec2ax3(const gp_Vec* p, const gp_Vec* v)
{
  return gp_Ax3(vec2pnt(p), vec2dir(v));
}

#define siren_pnt_get(mrb,val)    vec2pnt(siren_vec_get(mrb,val))
#define siren_dir_get(mrb,val)    vec2dir(siren_vec_get(mrb,val))
#define siren_ax1_get(mrb,p,v)    vec2ax1(siren_vec_get(mrb,p),siren_vec_get(mrb,v))
#define siren_ax2_get(mrb,p,n,vx) vec2ax2(siren_vec_get(mrb,p),siren_vec_get(mrb,n),siren_vec_get(mrb,vx))
#define siren_ax2s_get(mrb,p,v)   vec2ax2(siren_vec_get(mrb,p),siren_vec_get(mrb,v))
#define siren_ax3_get(mrb,p,n,vx) vec2ax3(siren_vec_get(mrb,p),siren_vec_get(mrb,n),siren_vec_get(mrb,vx))
#define siren_ax3s_get(mrb,p,v)   vec2ax3(siren_vec_get(mrb,p),siren_vec_get(mrb,v))

#endif
