#ifndef _COMMON_H_
#define _COMMON_H_

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
  gp_Pnt _p = vec2pnt(p);
  gp_Dir _v = vec2dir(v);
  return gp_Ax1(_p, _v);
}

inline gp_Ax2 vec2ax2(const gp_Vec* p, const gp_Vec* n, const gp_Vec* vx)
{
  gp_Pnt _p = vec2pnt(p);
  gp_Dir _n = vec2dir(n);
  gp_Dir _vx = vec2dir(vx);
  return gp_Ax2(_p, _n, _vx);
}

inline gp_Ax2 vec2ax2(const gp_Vec* p, const gp_Vec* v)
{
  gp_Pnt _p = vec2pnt(p);
  gp_Dir _v = vec2dir(v);
  return gp_Ax2(_p, _v);
}

inline gp_Ax3 vec2ax3(const gp_Vec* p, const gp_Vec* n, const gp_Vec* vx)
{
  gp_Pnt _p = vec2pnt(p);
  gp_Dir _n = vec2dir(n);
  gp_Dir _vx = vec2dir(vx);
  return gp_Ax3(_p, _n, _vx);
}

inline gp_Ax3 vec2ax3(const gp_Vec* p, const gp_Vec* v)
{
  gp_Pnt _p = vec2pnt(p);
  gp_Dir _v = vec2dir(v);
  return gp_Ax3(_p, _v);
}

#endif
