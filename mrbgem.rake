MRuby::Gem::Specification.new('mruby-siren') do |spec|

  # General spec
  spec.license = 'MIT'
  spec.author  = 'dyama'
  spec.summary = 'Easy 3D Geometry and Topology engine.'

  # define path
  use_oce = true
  occlibpath = '/opt/occ671/lib'
  occincpath = '/opt/occ671/inc'
  if use_oce
    occlibpath = '/opt/oce/lib'
    occincpath = '/opt/oce/include/oce'
  end

  # OCCT dependencies
  # Check http://dev.opencascade.org/doc/refman/html/index.html
  thirdPartyLibs =
    [ 'tbb' ]
  foundationClasses =
    [ 'TKernel', 'TKMath' ]
  modelingData =
    [ 'TKG2d', 'TKG3d', 'TKGeomBase', 'TKBRep' ]
  modelingAlgorithms =
    [ 'TKGeomAlgo', 'TKTopAlgo', 'TKBO', 'TKPrim',
      'TKShHealing', 'TKHLR', 'TKMesh', 'TKBool',
      'TKXMesh', 'TKFeat', 'TKFillet', 'TKOffset' ]
  visualization = []
  #  [ 'TKService', 'TKV3d', 'TKOpenGl', 'TKMeshVS',
  #    'TKNIS', 'TKVoxel' ]
  applicationFramework = []
  #  [ 'PTKernel', 'TKCDF', 'TKPShape', 'FWOSPlugin', 'TKLCAF',
  #    'TKShapeSchema', 'TKPLCAF', 'TKCAF', 'TKBinL', 'TKTObj',
  #    'TKXmlL', 'TKStdLSchema', 'TKPCAF', 'TKBin', 'TKBinTObj',
  #    'TKXml', 'TKXmlTObj', 'TKStdSchema' ]
  dataExchange = [ 'TKXSBase', 'TKSTL', 'TKIGES' ]

  # thirdPartyLibs =
  #   [ 'tbb' ]
  # foundationClasses =
  #   [ 'TKernel', 'TKMath' ]
  # modelingData =
  #   [ 'TKG2d', 'TKG3d', 'TKGeomBase', 'TKBRep' ]
  # modelingAlgorithms =
  #   [ 'TKGeomAlgo', 'TKTopAlgo', 'TKBO', 'TKPrim',
  #     'TKShHealing', 'TKHLR', 'TKMesh', 'TKBool',
  #     'TKXMesh', 'TKFeat', 'TKFillet', 'TKOffset' ]
  # visualization =
  #   [ 'TKService', 'TKV3d', 'TKOpenGl', 'TKMeshVS',
  #     'TKNIS', 'TKVoxel' ]
  # applicationFramework =
  #   [ 'PTKernel', 'TKCDF', 'TKPShape', 'FWOSPlugin', 'TKLCAF',
  #     'TKShapeSchema', 'TKPLCAF', 'TKCAF', 'TKBinL', 'TKTObj',
  #     'TKXmlL', 'TKStdLSchema', 'TKPCAF', 'TKBin', 'TKBinTObj',
  #     'TKXml', 'TKXmlTObj', 'TKStdSchema' ]
  # dataExchange =
  #   [ 'TKXSBase', 'TKSTL', 'TKVRML', 'TKSTEPBase', 'TKXCAF', 'TKIGES',
  #     'TKSTEP209', 'TKSTEPAttr', 'TKXCAFSchema', 'TKXmlXCAF', 'TKBinXCAF',
  #     'TKXDEIGES', 'TKSTEP', 'TKXDESTEP' ]

  allLibs = []
  allLibs <<
    thirdPartyLibs << foundationClasses << modelingData << modelingAlgorithms <<
    visualization << applicationFramework << dataExchange

  # Linker option
  spec.linker.library_paths << [ occlibpath ]

  spec.linker.libraries << allLibs

  # Compiler option
  spec.cxx.flags << "-L" << occlibpath << " -I" << occincpath <<
    "-Wno-unused-function -Wno-unused-variable"

  #allLibs.each do |libname|
  #  spec.cxx.flags << " -l" << libname
  #end

end

