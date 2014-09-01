#include "siren.h"

#include "vec.h"
#include "shape.h"
#include "build.h"
#include "exp.h"
#include "brepio.h"
#include "trans.h"
#include "prim.h"
#include "bool.h"
#include "iges.h"
#include "gprop.h"
#include "offset.h"

extern "C" {

  // initializer
  void mrb_mruby_siren_gem_init(mrb_state* mrb)
  {
    struct RClass* _shape  = NULL;
    struct RClass* _build  = NULL;
    struct RClass* _vec    = NULL;
    struct RClass* _exp    = NULL;
    struct RClass* _brepio = NULL;
    struct RClass* _trans  = NULL;
    struct RClass* _prim   = NULL;
    struct RClass* _bool   = NULL;
    struct RClass* _iges   = NULL;
    struct RClass* _gprop  = NULL;
    struct RClass* _offset = NULL;
    siren_shape_install(mrb, _shape);
    siren_build_install(mrb, _build);
    siren_vec_install(mrb, _vec);
    siren_exp_install(mrb, _exp);
    siren_brepio_install(mrb, _brepio);
    siren_trans_install(mrb, _trans);
    siren_prim_install(mrb, _prim);
    siren_bool_install(mrb, _bool);
    siren_iges_install(mrb, _iges);
    siren_gprop_install(mrb, _gprop);
    siren_offset_install(mrb, _offset);
    return;
  }

  // finalizer
  void mrb_mruby_siren_gem_final(mrb_state* mrb)
  {
    return;
  }

}
