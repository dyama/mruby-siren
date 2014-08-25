#include "siren.h"

#include "vec.h"
#include "shape.h"
#include "build.h"
#include "brepio.h"

extern "C" {

  // initializer
  void mrb_mruby_siren_gem_init(mrb_state* mrb)
  {
    struct RClass* _shape = NULL, *_build = NULL, *_vec = NULL, *_brepio = NULL;
    mrb_siren_shape_install(mrb, _shape);
    mrb_siren_build_install(mrb, _build);
    mrb_siren_vec_install(mrb, _vec);
    mrb_siren_brepio_install(mrb, _brepio);
    return;
  }

  // finalizer
  void mrb_mruby_siren_gem_final(mrb_state* mrb)
  {
    return;
  }

}
