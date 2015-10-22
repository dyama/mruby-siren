#include "siren.h"

#include "vec.h"
#include "loc.h"
#include "curve.h"
#include "shape.h"
#include "build.h"
#include "brepio.h"
#include "trans.h"
#include "prim.h"
#include "iges.h"
#include "offset.h"
#include "heal.h"
#include "bndbox.h"

#ifdef SIREN_ENABLE_STL
  #include "stl.h"
#endif

extern "C" {

  // initializer
  void mrb_mruby_siren_gem_init(mrb_state* mrb)
  {
    struct RClass* _loc    = NULL;
    struct RClass* _curve  = NULL;
    struct RClass* _shape  = NULL;
    struct RClass* _build  = NULL;
    struct RClass* _vec    = NULL;
    struct RClass* _brepio = NULL;
    struct RClass* _trans  = NULL;
    struct RClass* _prim   = NULL;
    struct RClass* _iges   = NULL;
    struct RClass* _offset = NULL;
    struct RClass* _heal   = NULL;
    struct RClass* _bndbox = NULL;
#ifdef SIREN_ENABLE_STL
    struct RClass* _stl    = NULL;
#endif

    siren_loc_install(mrb, _loc);
    siren_curve_install(mrb, _curve);
    siren_shape_install(mrb, _shape);
    siren_build_install(mrb, _build);
    siren_vec_install(mrb, _vec);
    siren_brepio_install(mrb, _brepio);
    siren_trans_install(mrb, _trans);
    siren_prim_install(mrb, _prim);
    siren_iges_install(mrb, _iges);
    siren_offset_install(mrb, _offset);
    siren_heal_install(mrb, _heal);
    siren_bndbox_install(mrb, _bndbox);
#ifdef SIREN_ENABLE_STL
    siren_stl_install(mrb, _stl);
#endif

    return;
  }

  // finalizer
  void mrb_mruby_siren_gem_final(mrb_state* mrb)
  {
    return;
  }

}
