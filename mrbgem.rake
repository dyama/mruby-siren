##
# mruby-siren rake file
#

MRuby::Gem::Specification.new('mruby-siren') do |spec|

  # General spec
  spec.author  = 'dyama'
  spec.summary = 'Easy 3D Geometry and Topology engine.'
  spec.license = 'MIT license'

  # define path
  occlibpath = [ '/opt/occ690/lib' ]
  occincpath = [ '/opt/occ690/inc' ]
  sirenincpath = File.expand_path(File.dirname(__FILE__)) + '/inc'

  # OCCT dependencies
  # Check http://dev.opencascade.org/doc/refman/html/index.html
  thirdPartyLibs = [ 'tbb', 'gl2ps', 'freetype', 'freeimage' ]

  if ENV['OS'] == 'Windows_NT'
    occlibpath = [ 'E:/occ/OCE-0.17-Mingw32/Win32/lib' ]
    occincpath = [ 'E:/occ/OCE-0.17-Mingw32/include/oce' ]
    thirdPartyLibs = [ 'freetype' ]
  end

  foundationClasses =
    [ 'TKernel', 'TKMath' ]
  modelingData =
    [ 'TKG2d', 'TKG3d', 'TKGeomBase', 'TKBRep' ]
  modelingAlgorithms =
    [ 'TKGeomAlgo', 'TKTopAlgo', 'TKBO', 'TKPrim',
      'TKShHealing', 'TKHLR', 'TKMesh', 'TKBool',
      'TKXMesh', 'TKFeat', 'TKFillet', 'TKOffset' ]
  visualization =
     [ 'TKService', 'TKV3d', 'TKOpenGl', 'TKMeshVS',
       'TKNIS', 'TKVoxel' ]
  applicationFramework =
    [ 'PTKernel', 'TKCDF', 'TKPShape', 'FWOSPlugin', 'TKLCAF',
      'TKShapeSchema', 'TKPLCAF', 'TKCAF', 'TKBinL', 'TKTObj',
      'TKXmlL', 'TKStdLSchema', 'TKPCAF', 'TKBin', 'TKBinTObj',
      'TKXml', 'TKXmlTObj', 'TKStdSchema' ]
  dataExchange =
    [ 'TKXSBase', 'TKSTL', 'TKVRML', 'TKSTEPBase', 'TKXCAF', 'TKIGES',
      'TKSTEP209', 'TKSTEPAttr', 'TKXCAFSchema', 'TKXmlXCAF', 'TKBinXCAF',
      'TKXDEIGES', 'TKSTEP', 'TKXDESTEP' ]

  # applicationFramework = []
  # dataExchange = [ 'TKXSBase', 'TKSTL', 'TKIGES' ]

  allLibs =
    thirdPartyLibs << foundationClasses << modelingData << modelingAlgorithms <<
    visualization << applicationFramework << dataExchange

  # Linker option
  spec.linker.library_paths << occlibpath
  spec.linker.libraries << allLibs

  # Compiler option
  spec.cxx.flags << occincpath.map{|n| "-I\"#{n}\"" } << " -I\"#{sirenincpath}\"" <<
    "-Wno-unused-function -Wno-unused-variable -Wno-unknown-pragmas"
end

