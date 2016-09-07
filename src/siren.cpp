#include "siren.h"

#include "vec.h"
#include "curve.h"
#include "shape.h"
#include "topalgo.h"
#include "brep.h"
#include "trans.h"
#include "prim.h"
#include "bndbox.h"
#include "filler.h"

#ifdef SIREN_ENABLE_SHHEALING
  #include "heal.h"
#endif

#ifdef SIREN_ENABLE_OFFSET
  #include "offset.h"
#endif

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

  struct RClass* mod_siren;

  // initializer
  void mrb_mruby_siren_gem_init(mrb_state* mrb)
  {
    // Siren module
    mod_siren  = mrb_define_module(mrb, "Siren");
    // classes
    siren_bndbox_install (mrb, mod_siren);
    siren_curve_install  (mrb, mod_siren);
    siren_filler_install (mrb, mod_siren);
    siren_shape_install  (mrb, mod_siren);
    siren_trans_install  (mrb, mod_siren);
    siren_vec_install    (mrb, mod_siren);
    // methods
    siren_topalgo_install(mrb, mod_siren);
    siren_brep_install   (mrb, mod_siren);
    siren_prim_install   (mrb, mod_siren);
#ifdef SIREN_ENABLE_OFFSET
    siren_offset_install (mrb, mod_siren);
#endif
#ifdef SIREN_ENABLE_IGES
    siren_iges_install   (mrb, mod_siren);
#endif
#ifdef SIREN_ENABLE_STL
    siren_stl_install    (mrb, mod_siren);
#endif
#ifdef SIREN_ENABLE_STEP
    siren_step_install   (mrb, mod_siren);
#endif
    return;
  }

  // finalizer
  void mrb_mruby_siren_gem_final(mrb_state* mrb)
  {
    return;
  }

}
