##
# mruby-siren rake file
#

MRuby::Gem::Specification.new('mruby-siren') do |spec|

  # General spec
  spec.author  = 'dyama'
  spec.summary = 'Lightweight 3D operation environment. See http://siren.xyz/'
  spec.license = 'MIT license'

  # siren configuration
  spec.add_dependency 'mruby-io'
  siren_incdir   = "#{dir}/inc"
  siren_incpaths = []
  siren_incpaths << siren_incdir
  siren_incpaths << Dir.glob("#{siren_incdir}/*/").map{|f| f.relative_path_from(dir)}

  # Open CASCADE Technology configuration
  # Check http://dev.opencascade.org/doc/refman/html/index.html
  thirdparty_libs = []
  occt_libpaths   = []
  occt_incpaths   = []

  if occt_libpaths.size == 0 and occt_incpaths.size == 0
    os = RbConfig::CONFIG['host_os'].downcase
    case os
    when /linux|solaris|bsd/
      occt_libpaths = [ '/opt/occ/710/lin64/gcc/lib' ]
      occt_incpaths = [ '/opt/occ/710/inc' ]
    when /darwin|mac os/
      occt_libpaths = [ '/usr/local/opt/opencascade/lib' ]
      occt_incpaths = [ '/usr/local/opt/opencascade/include/opencascade' ]
    when /mswin|mingw/
      occt_libpaths = [ '\occ\700\mingw32\gcc\lib' ]
      occt_incpaths = [ '\occ\700\inc' ]
      spec.cxx.flags << '-D_USE_MATH_DEFINES'
      spec.cxx.flags << '-D__NO_INLINE__'
    end
  end

  occt_libs = [
    # Foundation classes
    'TKernel', 'TKMath',
    # Modeling data
    'TKG2d', 'TKG3d', 'TKGeomBase', 'TKBRep',
    # Modeling algorithms
    'TKGeomAlgo', 'TKTopAlgo', 'TKBO', 'TKPrim',
    'TKShHealing', 'TKHLR', 'TKMesh', 'TKBool',
    'TKXMesh', 'TKFeat', 'TKFillet', 'TKOffset',
    # Data excange
    'TKXSBase', 'TKSTL', 'TKIGES', 'TKSTEP',
    'TKSTEP209', 'TKSTEPAttr', 'TKSTEPBase',
  ]

  # Linker option
  spec.linker.library_paths << occt_libpaths
  spec.linker.libraries << occt_libs << thirdparty_libs

  # Compiler option
  spec.cxx.flags << "-Wno-unused-function"
  spec.cxx.flags << "-Wno-unused-variable"
  spec.cxx.flags << "-Wno-unknown-pragmas"
  spec.cxx.flags << "-std=c++11"
  spec.cxx.include_paths << occt_incpaths
  spec.cxx.include_paths << siren_incpaths
  spec.objs << Dir.glob("#{dir}/src/*.{c,cpp}").map { |f| objfile(f.relative_path_from(dir).pathmap("#{build_dir}/%X")) }
  spec.objs << Dir.glob("#{dir}/src/*/*.{c,cpp}").map { |f| objfile(f.relative_path_from(dir).pathmap("#{build_dir}/%X")) }

end

