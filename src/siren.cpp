#include "siren.h"

#include "vec.h"
#include "curve.h"
#include "shape.h"
#include "build.h"
#include "brep.h"
#include "trans.h"
#include "prim.h"
#include "offset.h"
#include "heal.h"
#include "bndbox.h"
#include "filler.h"

#ifdef SIREN_ENABLE_IGES
  #include "iges.h"
#endif

#ifdef SIREN_ENABLE_STL
  #include "stl.h"
#endif

#ifdef SIREN_ENABLE_STEP
  #include "step.h"
#endif

extern "C" {

  // initializer
  void mrb_mruby_siren_gem_init(mrb_state* mrb)
  {
    struct RClass* mod_siren  = mrb_define_module(mrb, "Siren");

    struct RClass* _curve  = NULL;
    struct RClass* _shape  = NULL;
    struct RClass* _vec    = NULL;
    struct RClass* _trans  = NULL;
    struct RClass* _offset = NULL;
    struct RClass* _heal   = NULL;
    struct RClass* _bndbox = NULL;
    struct RClass* _filler = NULL;

    siren_curve_install(mrb, _curve);
    siren_shape_install(mrb, _shape);
    siren_vec_install(mrb, _vec);
    siren_trans_install(mrb, _trans);
    siren_build_install(mrb, mod_siren);
    siren_brep_install(mrb, mod_siren);
    siren_prim_install(mrb, mod_siren);
    siren_offset_install(mrb, _offset);
    siren_heal_install(mrb, _heal);
    siren_bndbox_install(mrb, _bndbox);
    siren_filler_install(mrb, _filler);
#ifdef SIREN_ENABLE_IGES
    siren_iges_install(mrb, mod_siren);
#endif
#ifdef SIREN_ENABLE_STL
    siren_stl_install(mrb, mod_siren);
#endif
#ifdef SIREN_ENABLE_STEP
    siren_step_install(mrb, mod_siren);
#endif
    return;
  }

  // finalizer
  void mrb_mruby_siren_gem_final(mrb_state* mrb)
  {
    return;
  }

}
