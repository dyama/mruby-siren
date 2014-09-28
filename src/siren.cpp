#include "siren.h"

#include "vec.h"
#include "shape.h"
#include "build.h"
#include "brepio.h"
#include "trans.h"
#include "prim.h"
#include "bool.h"
#include "iges.h"
#include "gprop.h"
#include "offset.h"
#include "algo.h"
#include "heal.h"
#include "feat.h"
#include "base.h"
#include "bndbox.h"
#include "world.h"
#include "camera.h"
#include "skin.h"

extern "C" {

  // initializer
  void mrb_mruby_siren_gem_init(mrb_state* mrb)
  {
    struct RClass* _shape  = NULL;
    struct RClass* _build  = NULL;
    struct RClass* _vec    = NULL;
    struct RClass* _brepio = NULL;
    struct RClass* _trans  = NULL;
    struct RClass* _prim   = NULL;
    struct RClass* _bool   = NULL;
    struct RClass* _iges   = NULL;
    struct RClass* _gprop  = NULL;
    struct RClass* _offset = NULL;
    struct RClass* _algo   = NULL;
    struct RClass* _heal   = NULL;
    struct RClass* _feat   = NULL;
    struct RClass* _base   = NULL;
    struct RClass* _bndbox = NULL;
    struct RClass* _world = NULL;
    struct RClass* _camera = NULL;
    struct RClass* _skin = NULL;
    siren_shape_install(mrb, _shape);
    siren_build_install(mrb, _build);
    siren_vec_install(mrb, _vec);
    siren_brepio_install(mrb, _brepio);
    siren_trans_install(mrb, _trans);
    siren_prim_install(mrb, _prim);
    siren_bool_install(mrb, _bool);
    siren_iges_install(mrb, _iges);
    siren_gprop_install(mrb, _gprop);
    siren_offset_install(mrb, _offset);
    siren_algo_install(mrb, _algo);
    siren_heal_install(mrb, _heal);
    siren_feat_install(mrb, _feat);
    siren_base_install(mrb, _base);
    siren_bndbox_install(mrb, _bndbox);
    siren_world_install(mrb, _world);
    siren_camera_install(mrb, _camera);
    siren_skin_install(mrb, _skin);
    return;
  }

  // finalizer
  void mrb_mruby_siren_gem_final(mrb_state* mrb)
  {
    return;
  }

}
