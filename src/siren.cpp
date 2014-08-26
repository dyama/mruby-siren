#include "siren.h"

#include "vec.h"
#include "shape.h"
#include "build.h"
#include "exp.h"
#include "brepio.h"
#include "trans.h"

extern "C" {

  // initializer
  void mrb_mruby_siren_gem_init(mrb_state* mrb)
  {
    struct RClass* _shape = NULL, *_build = NULL, *_vec = NULL, *_exp = NULL, *_brepio = NULL,
      *_trans = NULL;
    mrb_siren_shape_install(mrb, _shape);
    mrb_siren_build_install(mrb, _build);
    mrb_siren_vec_install(mrb, _vec);
    mrb_siren_exp_install(mrb, _exp);
    mrb_siren_brepio_install(mrb, _brepio);
    mrb_siren_trans_install(mrb, _trans);
    return;
  }

  // finalizer
  void mrb_mruby_siren_gem_final(mrb_state* mrb)
  {
    return;
  }

}
